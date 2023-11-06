#include<bits/stdc++.h>
using namespace std;

struct node{
    int data;
    node* next;
};

node* head=NULL,*temp;

void insert(int data){
   node *newnode=new node;
   newnode->data=data;
   newnode->next=NULL;
   if(head==NULL){
    head=temp=newnode;
   }
   else{
    temp->next=newnode;
    temp=newnode;
   }
}

void reverse(){
    node *prev=NULL,*temp,*cur=head;
    while(cur!=NULL){
        temp=cur->next;
        cur->next=prev;
        prev=cur;
        cur=temp;
    }
 head=prev;
}

node *Delete(int item){
    node *temp,*prev;
    temp=prev=head;
    if(head->data==item){
        head=head->next;
        return head;
    }
    else {
        while(2){
            head=head->next;
            if(head->data==item){
                prev->next=head->next;
                delete head;
                return temp;
            }
            else prev=prev->next;
        }
    }
}

void print(node* head){
    node* temp=head;
    while(temp!=NULL){
        cout<<temp->data<<" "<<temp->next<<endl;
        temp=temp->next;
    }
}

int main(){
    insert(5);
    insert(4);
    insert(6);
    insert(8);
    insert(1);
    insert(9);
    print(head);
   // reverse();
   head=Delete(9);
    print(head);

}
