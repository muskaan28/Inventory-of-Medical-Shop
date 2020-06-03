/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>

  struct hash *hashTable = NULL;
  int eleCount = 0;

  struct node {
        int mg,qty;
        float price;
        char name[100];
        struct node *next;
  };

  struct hash {
        struct node *head;
        int count;
  };

  struct node * createNode(int mg, char *name,int qty,float price) {
        struct node *newnode;
        newnode=(struct node *)malloc(sizeof(struct node));
        newnode->mg=mg;
        newnode->qty=qty;
        newnode->price=price;
        strcpy(newnode->name,name);
        newnode->next=NULL;
        return newnode;
  }


  void insertToHash(int mg, char *name,int qty, float price) {
        int hashIndex=mg%eleCount;
        struct node *newnode=createNode(mg,name,qty,price);
        if (!hashTable[hashIndex].head) {
                hashTable[hashIndex].head = newnode;
                hashTable[hashIndex].count = 1;
                return;
        }
        newnode->next=(hashTable[hashIndex].head);
        hashTable[hashIndex].head = newnode;
        hashTable[hashIndex].count++;
        return;
  }


  void deleteFromHash(int mg) {
        int hashIndex = mg % eleCount, flag = 0;
        struct node *temp, *myNode;
        myNode = hashTable[hashIndex].head;
        if (!myNode) {
                printf("Given data is not present in hash Table!!\n");
                return;
        }
        temp = myNode;
        while (myNode!=NULL) {
                if (myNode->mg == mg) {
                        flag = 1;
                        if (myNode == hashTable[hashIndex].head)
                                hashTable[hashIndex].head = myNode->next;
                        else
                                temp->next = myNode->next;

                        hashTable[hashIndex].count--;
                        free(myNode);
                        break;
                }
                temp = myNode;
                myNode = myNode->next;
        }
        if (flag)
                printf("Data deleted successfully from Hash Table\n");
        else
                printf("Given data is not present in hash Table!!!!\n");
        return;
  }

  void searchInHash(int mg) {
        int hashIndex = mg % eleCount, flag = 0;
        struct node *myNode;
        myNode = hashTable[hashIndex].head;
        if (!myNode) {
                printf("Search element unavailable in hash table\n");
                return;
        }
        while (myNode != NULL) {
                if (myNode->mg == mg) {
                        printf("mg  : %d\n", myNode->mg);
                        printf("Name     : %s\n", myNode->name);
                        printf("qty     : %d\n", myNode->qty);
                        printf("price    : %f\n", myNode->price);
                        flag = 1;
                        break;
                }
                myNode = myNode->next;
        }
        if (!flag)
                printf("Search element unavailable in hash table\n");
        return;
  }

  void display() {
        struct node *myNode;
        int i;
        for (i = 0; i < eleCount; i++) {
                if (hashTable[i].count == 0)
                        continue;
                myNode = hashTable[i].head;
                if (!myNode)
                        continue;
                printf("\nData at index %d in Hash Table:\n", i);
                printf("mg           Name          qty           price   \n");
                printf("--------------------------------\n");
                while (myNode != NULL) {
                        printf("%-12d", myNode->mg);
                        printf("%-15s", myNode->name);
                        printf("%-10d", myNode->qty);
                        printf("Rs%f\n", myNode->price);
                        myNode = myNode->next;
                }
        }
        return;
  }

  int main() {
        int n, ch,mg,qty;
        char name[100];
        float price;
        printf("Enter the number of elements:");
        scanf("%d",& n);
        eleCount = n;
        hashTable = (struct hash *)calloc(n, sizeof (struct hash));
        while (1) {
                printf("\n1. Insertion\t2. Deletion\n");
                printf("3. Searching\t4. Display\n5. Exit\n");
                printf("Enter your choice:");
                scanf("%d",& ch);
                switch (ch) {
                        case 1:
                                printf("Enter the mg value:");
                                scanf("%d",& mg);
                                getchar();
                                printf("Name:");
                                fgets(name, 100, stdin);
                                name[strlen(name) - 1] = '\0';
                                printf("qty:");
                                scanf("%d",& qty);
                                printf("price:");
                                scanf("%f",& price);
                                insertToHash(mg,name,qty,price);
                                break;

                        case 2:
                                printf("Enter the mg to perform deletion:");
                                scanf("%d",& mg);
                                deleteFromHash(mg);
                                break;

                        case 3:
                                printf("Enter the mg to search:");
                                scanf("%d",& mg);
                                searchInHash(mg);
                                break;
                        case 4:
                                display();
                                break;
                        case 5:
                                exit(0);
                        default:
                                printf("U have entered wrong option!!\n");
                                break;
                }
        }
        return 0;
  }




