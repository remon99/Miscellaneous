# Container Damage Form Automation

Automated form-filling script for container damage/repair entries using **Selenium** + **Chrome debugger mode**.

The script reads data from an Excel file, fills a web form (shop code, equipment number, damage/repair codes, costs, remarks, images), and waits for you to open each new empty form before filling the next row.

---

## Prerequisites

| Requirement | Notes |
|-------------|-------|
| **Python 3.8+** | Recommended |
| **Google Chrome** | Must be installed |
| **ChromeDriver** | Matching your Chrome version (or use Selenium Manager / webdriver-manager) |
| **Python packages** | `pandas`, `openpyxl`, `selenium` |

Install packages:

```bash
pip install pandas openpyxl selenium
```

---

## 1. Prepare the Excel file

Create (or use) an Excel file with **exact column names**:

| Column Name        | Description                          | Example          |
|--------------------|--------------------------------------|------------------|
| `Container Number` | Equipment / container ID             | `MSCU1234567`    |
| `Size`             | Container size                       | `40 HC` or other |
| `Amount`           | Material cost                        | `150.50`         |
| `Booking Number`   | Booking reference                    | `123456789`      |
| `Bar`              | Number of bars (can be float)        | `22` or `13.45`  |
| `Ropes`            | Number of ropes                      | `25`             |
| `Straps`           | Number of straps                     | `10`             |
| `Stat`             | `1` = use Ropes, anything else = Straps | `1`           |

**Default path in the script:**

```
C:\Users\User\Desktop\automate.xlsx
```

Change the path in the script if needed:

```python
EXCEL_PATH = r"C:\Users\User\Desktop\automate.xlsx"
```

---

## 2. Prepare the images

Images must be named after the **Container Number**:

```
C:\Users\User\Desktop\img\
├── MSCU1234567.jpeg
├── MSCU1234567 (2).jpeg
├── MSCU7654321.jpeg
├── MSCU7654321 (2).jpeg
└── ...
```

- First image: `{Container Number}.jpeg`
- Second image: `{Container Number} (2).jpeg`

Update the folder path in the script if your images are elsewhere.

---

## 3. Start Chrome in debugger mode

1. Close **all** Chrome windows.
2. Open a terminal / Command Prompt and run:

**Windows:**

```cmd
"C:\Program Files\Google\Chrome\Application\chrome.exe" --remote-debugging-port=9222 --user-data-dir="C:\chrome-debug-profile"
```

**macOS:**

```bash
/Applications/Google\ Chrome.app/Contents/MacOS/Google\ Chrome --remote-debugging-port=9222 --user-data-dir="/tmp/chrome-debug-profile"
```

**Linux:**

```bash
google-chrome --remote-debugging-port=9222 --user-data-dir="/tmp/chrome-debug-profile"
```

3. A new Chrome window will open.  
4. Log in to the target website and navigate to the form page.

> The script connects to this already-running Chrome instance (`127.0.0.1:9222`).  
> Do **not** close this Chrome window while the script is running.

---

## 4. Run the script

1. Make sure Chrome is running with the debugger flag (step 3).
2. Open a terminal and run:

```bash
python your_script_name.py
```

3. The script will:
   - Load the Excel file
   - Wait until you open a **fresh empty form** (equipment number field must be empty)
   - Fill the entire form for the current row
   - Wait for you again for the next row

4. After each row is filled:
   - Review the form
   - Submit it manually
   - Open the next empty form when ready

---

## What the script fills automatically

| Field                    | Value / Logic                                      |
|--------------------------|----------------------------------------------------|
| Shop Code                | `9SD Asian Trade - Dhaka`                          |
| Equipment Number         | From `Container Number` column                     |
| Images (first section)   | Two images based on container number               |
| Damage Code              | Always `WT`                                        |
| Repair Code              | `0822` if Size = `40 HC`, otherwise `0821`         |
| Repair Location Code     | `IXXX`                                             |
| TPI Code                 | `W`                                                |
| Man Hours per Piece      | `0`                                                |
| Material Cost            | From `Amount` column                               |
| Images (second section)  | Same two images via paperclip modal                |
| Remark                   | `BOOKING NUMBER:{number}` + bars + ropes/straps    |

Remark example:

```
BOOKING NUMBER:123456789
22 BARS 25 ROPES
```

(or `STRAPS` depending on the `Stat` column)

---

## Important notes

- The script **waits for you** to open each new empty form. It does **not** submit the form or click “Next”.
- You must keep the Chrome debugger window open.
- Image paths and Excel path are hardcoded for Windows. Change them if you use a different OS or folder structure.
- If a field fails, the script prints an error and continues (or skips the row if Equipment ID fails).
- Always review the filled form before submitting.

---

## Troubleshooting

| Problem | Solution |
|---------|----------|
| `Chrome not reachable` / connection refused | Make sure Chrome was started with `--remote-debugging-port=9222` |
| Images not found | Check exact file names and folder path |
| Dropdown (Shop Code) not selecting | The page layout may have changed – inspect the options and adjust `select_shop_dhaka()` |
| Form fields not found | The website may have updated its selectors – inspect elements and update CSS selectors |
| Excel columns missing | Column names must match exactly (case-sensitive) |

---

## File structure recommendation

```
Desktop/
├── automate.xlsx
├── img/
│   ├── CONTAINER1.jpeg
│   ├── CONTAINER1 (2).jpeg
│   └── ...
└── container_automation.py   ← your script
```

---

## License / Usage

This script is provided as-is for personal/internal use.  
Modify paths, selectors, and logic as needed for your environment.
