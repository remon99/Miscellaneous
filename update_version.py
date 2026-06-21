import time
import math
import pandas as pd
from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.keys import Keys

# 1. Load your Excel
EXCEL_PATH = r"C:\Users\User\Desktop\automate.xlsx"
df = pd.read_excel(EXCEL_PATH)

# 2. Setup Chrome
options = Options()
options.debugger_address = "127.0.0.1:9222"
driver = webdriver.Chrome(options=options)
wait = WebDriverWait(driver, 20)

# ─────────────────────────────────────────────
# HELPER FUNCTIONS
# ─────────────────────────────────────────────

def input_custom_component(selector, value):
    try:
        element = wait.until(EC.element_to_be_clickable((By.CSS_SELECTOR, selector)))
        element.click()
        time.sleep(0.3)
        driver.execute_script("""
            var el = arguments[0];
            var val = arguments[1];
            el.value = val;
            el.dispatchEvent(new Event('input', { bubbles: true }));
            el.dispatchEvent(new Event('change', { bubbles: true }));
            el.dispatchEvent(new Event('blur',  { bubbles: true }));
        """, element, value)
        element.send_keys(Keys.TAB)
        time.sleep(0.5)
        print(f"  ✅ Set {selector} → {value}")
    except Exception as e:
        print(f"  ❌ Error filling {selector}: {e}")


def fill_typeahead_field(form_control_name, value):
    try:
        selector = f"mc-typeahead[formcontrolname='{form_control_name}']"
        element = wait.until(EC.element_to_be_clickable((By.CSS_SELECTOR, selector)))
        element.click()
        driver.execute_script("""
            var el = arguments[0];
            el.value = arguments[1];
            el.dispatchEvent(new Event('input',  { bubbles: true }));
            el.dispatchEvent(new Event('change', { bubbles: true }));
            el.dispatchEvent(new Event('blur',   { bubbles: true }));
        """, element, value)
        element.send_keys(Keys.TAB)
        time.sleep(0.5)
        print(f"  ✅ Filled {form_control_name} → {value}")
    except Exception as e:
        print(f"  ❌ Failed to fill {form_control_name}: {e}")

# ─────────────────────────────────────────────────────────────
# STEP: Select Shop Code → "9SD Asian Trade -Dhaka"
# mc-select uses shadow DOM mc-option elements, so we can't use
# a normal click. We find the Dhaka option and click it via JS.
# ─────────────────────────────────────────────────────────────
def select_shop_dhaka():
    try:
        # 1. Click to open dropdown
        shop_select = wait.until(EC.element_to_be_clickable(
            (By.CSS_SELECTOR, "mc-select[formcontrolname='shopCode']")))
        shop_select.click()
        time.sleep(1)  # Wait for options to fully render

        # 2. Now that dropdown is OPEN, try to find and click Dhaka option
        # Try multiple selectors since mc-option renders differently when open
        
        # Method A — find by full text inside any visible element
        try:
            dhaka = wait.until(EC.element_to_be_clickable(
                (By.XPATH, "//*[contains(., 'Dhaka') and not(*[contains(., 'Dhaka')])]")))
            dhaka.click()
            print("  ✅ Shop Code → Dhaka (deepest text node method)")
            time.sleep(0.5)
            return
        except:
            print("  ⚠️ Method A failed")

        # Method B — get ALL mc-option elements after dropdown opens and click index 1
        try:
            all_options = driver.find_elements(By.CSS_SELECTOR, "mc-option")
            print(f"  🔍 Found {len(all_options)} mc-option elements")
            for i, opt in enumerate(all_options):
                print(f"      Option {i}: text='{opt.text}' | innerHTML='{opt.get_attribute('innerHTML')[:80]}'")
            # Click the Dhaka one (index 1 based on your screenshot)
            driver.execute_script("arguments[0].click();", all_options[1])
            print("  ✅ Shop Code → Dhaka (index click method)")
            time.sleep(0.5)
            return
        except Exception as e:
            print(f"  ⚠️ Method B failed: {e}")

        # Method C — click by coordinate (last resort)
        # Dhaka appears just below Chittagong in the dropdown
        try:
            from selenium.webdriver.common.action_chains import ActionChains
            actions = ActionChains(driver)
            actions.move_to_element(shop_select).perform()
            # Move down ~40px from the select element to hit Dhaka option
            actions.move_by_offset(0, 80).click().perform()
            print("  ✅ Shop Code → Dhaka (coordinate click method)")
            time.sleep(0.5)
            return
        except Exception as e:
            print(f"  ⚠️ Method C failed: {e}")

    except Exception as e:
        print(f"  ❌ Shop Code failed entirely: {e}")


def wait_for_fresh_form():
    """
    Waits indefinitely until the equipment number field appears AND is empty.
    This means you've navigated to a fresh form — bot can start filling.
    """
    print("\n  ⏳ Waiting for you to open the next fresh form...")
    while True:
        try:
            eq_field = driver.find_element(By.CSS_SELECTOR, "mc-input[formcontrolname='equipmentNumber']")
            current_val = eq_field.get_attribute("value") or ""
            if current_val.strip() == "":
                print("  ✅ Fresh form detected! Starting automation...")
                return  # Form is ready, exit the wait loop
        except:
            pass  # Field not found yet, keep waiting
        time.sleep(1)  # Check every second


import os

# ── Image Upload (after equipment number step) ──────────────


def upload_images(row):
    try:
        # Get image paths from Excel row
        image1_path = f"C:\\Users\\User\\Desktop\\img\\{row['Container Number']}.jpeg"
        image2_path = f"C:\\Users\\User\\Desktop\\img\\{row['Container Number']} (2).jpeg"
        # Make sure both files exist before trying
        if not os.path.exists(image1_path):
            print(f"  ❌ Image 1 not found: {image1_path}")
            return
        if not os.path.exists(image2_path):
            print(f"  ❌ Image 2 not found: {image2_path}")
            return

        # 1. Find the hidden file input
        file_input = wait.until(EC.presence_of_element_located(
            (By.CSS_SELECTOR, "input[type='file'][accept*='image']")))

        # 2. Make it visible so Selenium can interact with it
        driver.execute_script("arguments[0].style.display = 'block';", file_input)
        time.sleep(0.3)

        # 3. Send both file paths at once (separated by \n for multiple files)
        file_input.send_keys(image1_path + "\n" + image2_path)

        time.sleep(1.5)  # Wait for upload preview to appear
        print(f"  ✅ Images uploaded: {os.path.basename(image1_path)}, {os.path.basename(image2_path)}")

    except Exception as e:
        print(f"  ❌ Image upload failed: {e}")


def upload_images_second_section(row):
    try:
        image1_path = rf"C:\Users\User\Desktop\img\{row['Container Number']}.jpeg"
        image2_path = rf"C:\Users\User\Desktop\img\{row['Container Number']} (2).jpeg"

        if not os.path.exists(image1_path):
            print(f"  ❌ Image 1 not found: {image1_path}")
            return
        if not os.path.exists(image2_path):
            print(f"  ❌ Image 2 not found: {image2_path}")
            return

        # 1. Click the paperclip button to open the modal
        paperclip_button = wait.until(EC.element_to_be_clickable(
            (By.CSS_SELECTOR, "mc-button[icon='paperclip']")))
        driver.execute_script("arguments[0].click();", paperclip_button)
        print("  ✅ Paperclip clicked, waiting for modal...")
        time.sleep(1.5)

        # 2. Target the file input inside the modal's app-file-input (compact type)
        file_input = wait.until(EC.presence_of_element_located(
            (By.CSS_SELECTOR, "app-file-input[type='compact'] input[type='file']")))

        # 3. Make it interactable and send both file paths
        driver.execute_script("arguments[0].style.display = 'block';", file_input)
        time.sleep(0.3)
        file_input.send_keys(image1_path + "\n" + image2_path)
        print(f"  ✅ Images uploaded in modal.")
        time.sleep(2)  # Wait for previews to appear

        # 4. Click Done to close the modal
        done_button = wait.until(EC.element_to_be_clickable(
            (By.CSS_SELECTOR, "mc-button[label='Done']")))
        driver.execute_script("arguments[0].click();", done_button)
        print("  ✅ Done clicked, modal closed.")
        time.sleep(1)

    except Exception as e:
        print(f"  ❌ Second section image upload failed: {e}")

def fill_row(row):
    """Fill the entire form for one Excel row."""

    # ── 0. Shop Code → Dhaka (must be first) ─────
    select_shop_dhaka()

    # ── Equipment ID ──────────────────────────────
    equipment_id = str(row['Container Number'])
    try:
        eq_container = wait.until(EC.presence_of_element_located(
            (By.CSS_SELECTOR, "mc-input[formcontrolname='equipmentNumber']")))
        eq_container.click()
        time.sleep(0.5)
        driver.execute_script("arguments[0].value = arguments[1];", eq_container, equipment_id)
        driver.execute_script("arguments[0].dispatchEvent(new Event('input', { bubbles: true }));", eq_container)
        driver.execute_script("arguments[0].dispatchEvent(new Event('blur',  { bubbles: true }));", eq_container)
        time.sleep(0.5)
        eq_container.send_keys(Keys.TAB)
        print(f"  ✅ Equipment ID → {equipment_id}")
    except Exception as e:
        print(f"  ❌ Equipment ID failed: {e}")
        return False  # Signal that this row failed
    
    upload_images(row)
    time.sleep(1)

    # ── Damage & Repair Codes ─────────────────────
    damage_val = "WT"
    repair_val = "0822" if str(row['Size']).strip() == '40 HC' else "0821"
    input_custom_component("mc-typeahead[formcontrolname='damageCode']", damage_val)
    input_custom_component("mc-typeahead[formcontrolname='repairCode']",  repair_val)

    # ── Repair Location & TPI ─────────────────────
    fill_typeahead_field("repairLocationCode", "IXXX")
    fill_typeahead_field("tpiCode",            "W")

    # ── Man Hrs/pc → 0 ───────────────────────────
    try:
        hrs_box = wait.until(EC.element_to_be_clickable(
            (By.CSS_SELECTOR, "mc-input[formcontrolname='manHoursPerPiece']")))
        driver.execute_script("""
            var el = arguments[0];
            el.value = '0';
            el.dispatchEvent(new Event('input',  { bubbles: true }));
            el.dispatchEvent(new Event('change', { bubbles: true }));
            el.dispatchEvent(new Event('blur',   { bubbles: true }));
        """, hrs_box)
        hrs_box.send_keys(Keys.TAB)
        print("  ✅ Man Hrs/pc → 0")
    except Exception as e:
        print(f"  ❌ Man Hrs/pc failed: {e}")

    # ── Material Cost ─────────────────────────────
    cost = str(row['Amount'])
    try:
        amount = wait.until(EC.presence_of_element_located(
            (By.CSS_SELECTOR, "mc-input[formcontrolname='materialCostPerPiece']")))
        amount.click()
        time.sleep(0.5)
        driver.execute_script("arguments[0].value = arguments[1];", amount, cost)
        driver.execute_script("arguments[0].dispatchEvent(new Event('input', { bubbles: true }));", amount)
        driver.execute_script("arguments[0].dispatchEvent(new Event('blur',  { bubbles: true }));", amount)
        time.sleep(0.5)
        print(f"  ✅ Material cost → {cost}")
    except Exception as e:
        print(f"  ❌ Amount failed: {e}")

    upload_images_second_section(row)
    time.sleep(1)

    # ── Remark ────────────────────────────────────
    booking_number = str(int(row['Booking Number']))
    bars           = math.ceil(int(float(row['Bar'])))      # e.g. 22.0 → 22, 13.45 → 14
    ropes          = math.ceil(int(float(row['Ropes'])))    # e.g. 25.0 → 25, 13.45 → 14
    straps         = math.ceil(int(float(row['Straps'])))   # e.g. 25.0 → 25, 13.45 → 14

    additional_info = (f"{ropes} ROPES") if str(row['Stat']) == '1' else (f"{straps} STRAPS")
    remark_info     = f"BOOKING NUMBER:{booking_number}\n{bars} BARS {additional_info}"

    try:
        wait.until(EC.presence_of_element_located(
            (By.CSS_SELECTOR, "mc-textarea[formcontrolname='remark']")))
        driver.execute_script("""
            const comp     = document.querySelector("mc-textarea[formcontrolname='remark']");
            const textarea = comp.shadowRoot
                ? comp.shadowRoot.querySelector("textarea")
                : comp.querySelector("textarea");
            const nativeSetter = Object.getOwnPropertyDescriptor(
                window.HTMLTextAreaElement.prototype, "value").set;
            nativeSetter.call(textarea, arguments[0]);
            textarea.dispatchEvent(new Event('input',  { bubbles: true }));
            comp.dispatchEvent(new Event('change', { bubbles: true }));
            comp.dispatchEvent(new Event('blur',   { bubbles: true }));
        """, remark_info)
        print(f"  ✅ Remark → {remark_info}")
    except Exception as e:
        print(f"  ❌ Remark failed: {e}")

    return True  # Row completed successfully


# ─────────────────────────────────────────────
# MAIN LOOP
# ─────────────────────────────────────────────

print(f"📋 Loaded {len(df)} rows from Excel.")
print("👉 Please navigate to the first form page in the browser to begin.\n")

for index, row in df.iterrows():
    print(f"\n{'='*50}")
    print(f"  ROW {index + 1} of {len(df)} | Container: {row['Container Number']}")
    print(f"{'='*50}")

    # Wait until YOU open a fresh empty form
    wait_for_fresh_form()

    # Bot fills everything
    success = fill_row(row)

    if success:
        print(f"\n  ✅ Row {index + 1} done! Please verify and submit.")
        print("  ➡️  Then navigate to the next fresh form when ready.")
    else:
        print(f"\n  ⚠️  Row {index + 1} had issues. Check the form before submitting.")
        print("  ➡️  Navigate to the next fresh form when ready.")

print("\n🎉 All rows processed!")
input("Press Enter to close...")