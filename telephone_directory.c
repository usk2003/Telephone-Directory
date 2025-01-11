#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Contact Node Structure
struct node {
    char number[100];
    char gmail[100];
    char name[100];
    struct node *prev, *next;
} *head = NULL;

// Priority Queue for Favorite Contacts
struct pq {
    char number[100];
    char gmail[100];
    char name[100];
    int priority;
    struct pq *previous, *nextt;
} *top = NULL;

// Function Prototypes
void insert();
void display();
void update();
void deletecontact();
void deletesamename();
void deletesamegmail();
void deletesamenumber();
void searchbyname(char *name);
void searchbynumber(char *num);
void searchbygmail(char *gm);
void createFav();
void displayFav();
void sort();

// Insert Contact
void insert() {
    char number[100], gmail[100], name[100], ans;
    do {
        struct node *p = (struct node *)malloc(sizeof(struct node));
        printf("Enter The Name of The Contact: ");
        scanf(" %[^\n]", name);
        strcpy(p->name, name);

        printf("Enter The Phone Number: ");
        scanf(" %[^\n]", number);
        while (strlen(number) != 10) {
            printf("Enter a valid 10-digit number: ");
            scanf(" %[^\n]", number);
        }
        strcpy(p->number, number);

        printf("Enter The G-Mail ID: ");
        scanf(" %[^\n]", gmail);
        strcpy(p->gmail, gmail);

        if (head == NULL) {
            p->next = p->prev = NULL;
            head = p;
        } else {
            struct node *tmp = head;
            while (tmp->next != NULL) tmp = tmp->next;
            p->next = NULL;
            p->prev = tmp;
            tmp->next = p;
        }
        printf("Do You Want To Continue Insertion? (y/n): ");
        scanf(" %c", &ans);
    } while (ans == 'y');
}

// Display Contacts
void display() {
    struct node *tmp = head;
    if (!tmp) {
        printf("Phone book is empty.\n");
        return;
    }
    printf("\nYour Phone Book:\n");
    while (tmp != NULL) {
        printf("\nName: %s\nNumber: +91-%s\nG-Mail: %s\n", tmp->name, tmp->number, tmp->gmail);
        tmp = tmp->next;
    }
}

// Update Contact
void update() {
    char n[100], ans;
    int c;
    printf("\nEnter the Name of the Contact to Update: ");
    scanf(" %[^\n]", n);

    struct node *tmp = head;
    while (tmp != NULL) {
        if (strcmp(n, tmp->name) == 0) {
            do {
                printf("\n1. Update Name\n2. Update Phone Number\n3. Update G-Mail\n");
                scanf("%d", &c);
                switch (c) {
                    case 1:
                        printf("Enter New Name: ");
                        scanf(" %[^\n]", tmp->name);
                        break;
                    case 2:
                        printf("Enter New Phone Number: ");
                        scanf(" %[^\n]", tmp->number);
                        while (strlen(tmp->number) != 10) {
                            printf("Enter a valid 10-digit number: ");
                            scanf(" %[^\n]", tmp->number);
                        }
                        break;
                    case 3:
                        printf("Enter New G-Mail: ");
                        scanf(" %[^\n]", tmp->gmail);
                        break;
                    default:
                        printf("Invalid choice.\n");
                }
                printf("Do You Want To Continue Updating? (y/n): ");
                scanf(" %c", &ans);
            } while (ans == 'y');
            return;
        }
        tmp = tmp->next;
    }
    printf("Contact not found.\n");
}

// Delete Contact
void deletecontact() {
    char s[100];
    printf("Enter the Name of the Contact to Delete: ");
    scanf(" %[^\n]", s);

    struct node *tmp = head;
    while (tmp != NULL) {
        if (strcmp(s, tmp->name) == 0) {
            if (tmp == head) {
                head = head->next;
                if (head) head->prev = NULL;
            } else {
                tmp->prev->next = tmp->next;
                if (tmp->next) tmp->next->prev = tmp->prev;
            }
            free(tmp);
            printf("Contact deleted successfully.\n");
            return;
        }
        tmp = tmp->next;
    }
    printf("Contact not found.\n");
}

// Delete Duplicate Names
void deletesamename() {
    struct node *tmp1 = head;
    int found = 0;
    while (tmp1 && tmp1->next) {
        struct node *tmp2 = tmp1;
        while (tmp2->next) {
            if (strcmp(tmp1->name, tmp2->next->name) == 0) {
                struct node *dup = tmp2->next;
                tmp2->next = dup->next;
                if (dup->next) dup->next->prev = tmp2;
                free(dup);
                found = 1;
            } else {
                tmp2 = tmp2->next;
            }
        }
        tmp1 = tmp1->next;
    }
    if (!found) printf("No duplicate names found.\n");
    else display();
}

// Delete Duplicate G-Mail IDs
void deletesamegmail() {
    struct node *tmp1 = head;
    int found = 0;
    while (tmp1 && tmp1->next) {
        struct node *tmp2 = tmp1;
        while (tmp2->next) {
            if (strcmp(tmp1->gmail, tmp2->next->gmail) == 0) {
                struct node *dup = tmp2->next;
                tmp2->next = dup->next;
                if (dup->next) dup->next->prev = tmp2;
                free(dup);
                found = 1;
            } else {
                tmp2 = tmp2->next;
            }
        }
        tmp1 = tmp1->next;
    }
    if (!found) printf("No duplicate G-Mail IDs found.\n");
    else display();
}

// Delete Duplicate Numbers
void deletesamenumber() {
    struct node *tmp1 = head;
    int found = 0;
    while (tmp1 && tmp1->next) {
        struct node *tmp2 = tmp1;
        while (tmp2->next) {
            if (strcmp(tmp1->number, tmp2->next->number) == 0) {
                struct node *dup = tmp2->next;
                tmp2->next = dup->next;
                if (dup->next) dup->next->prev = tmp2;
                free(dup);
                found = 1;
            } else {
                tmp2 = tmp2->next;
            }
        }
        tmp1 = tmp1->next;
    }
    if (!found) printf("No duplicate numbers found.\n");
    else display();
}

// Search by Name
void searchbyname(char *name) {
    struct node *tmp = head;
    while (tmp != NULL) {
        if (strcmp(name, tmp->name) == 0) {
            printf("\nName: %s\nNumber: +91-%s\nG-Mail: %s\n", tmp->name, tmp->number, tmp->gmail);
            return;
        }
        tmp = tmp->next;
    }
    printf("Contact not found.\n");
}

// Search by Number
void searchbynumber(char *num) {
    struct node *tmp = head;
    while (tmp != NULL) {
        if (strcmp(num, tmp->number) == 0) {
            printf("\nName: %s\nNumber: +91-%s\nG-Mail: %s\n", tmp->name, tmp->number, tmp->gmail);
            return;
        }
        tmp = tmp->next;
    }
    printf("Contact not found.\n");
}

// Search by G-Mail
void searchbygmail(char *gm) {
    struct node *tmp = head;
    while (tmp != NULL) {
        if (strcmp(gm, tmp->gmail) == 0) {
            printf("\nName: %s\nNumber: +91-%s\nG-Mail: %s\n", tmp->name, tmp->number, tmp->gmail);
            return;
        }
        tmp = tmp->next;
    }
    printf("Contact not found.\n");
}

// Create Favorite Contacts
void createFav() {
    char name[100];
    int priority;
    printf("Enter the Name of the Contact and Priority: ");
    scanf(" %[^\n]", name);
    scanf("%d", &priority);

    struct node *tmp = head;
    while (tmp) {
        if (strcmp(name, tmp->name) == 0) {
            struct pq *p = (struct pq *)malloc(sizeof(struct pq));
            strcpy(p->name, tmp->name);
            strcpy(p->number, tmp->number);
            strcpy(p->gmail, tmp->gmail);
            p->priority = priority;

            if (!top) {
                p->nextt = p->previous = NULL;
                top = p;
            } else {
                struct pq *temp = top;
                while (temp->nextt && temp->priority <= priority) {
                    temp = temp->nextt;
                }
                p->nextt = temp->nextt;
                p->previous = temp;
                if (temp->nextt) temp->nextt->previous = p;
                temp->nextt = p;
            }
            return;
        }
        tmp = tmp->next;
    }
    printf("Contact not found.\n");
}

// Display Favorite Contacts
void displayFav() {
    struct pq *temp = top;
    if (!temp) {
        printf("No favorite contacts.\n");
        return;
    }
    printf("\nFavorite Contacts:\n");
    while (temp) {
        printf("\nName: %s\nNumber: +91-%s\nG-Mail: %s\nPriority: %d\n", temp->name, temp->number, temp->gmail, temp->priority);
        temp = temp->nextt;
    }
}

// Sort Contacts
void sort() {
    struct node *i, *j;
    char temp[100];
    for (i = head; i && i->next; i = i->next) {
        for (j = i->next; j; j = j->next) {
            if (strcmp(i->name, j->name) > 0) {
                // Swap names
                strcpy(temp, i->name);
                strcpy(i->name, j->name);
                strcpy(j->name, temp);

                // Swap numbers
                strcpy(temp, i->number);
                strcpy(i->number, j->number);
                strcpy(j->number, temp);

                // Swap G-Mail
                strcpy(temp, i->gmail);
                strcpy(i->gmail, j->gmail);
                strcpy(j->gmail, temp);
            }
        }
    }
}

// Main Function
int main() {
    int ch;
    char name[100], number[100], gmail[100];

    printf("\nWelcome to Phone Book\n");
    insert();
    sort();

    while (1) {
        printf("\n1) Display Phone Book\n2) Insert New Contact\n3) Update Contact\n4) Delete Contact\n");
        printf("5) Delete Duplicate Names\n6) Delete Duplicate Numbers\n7) Delete Duplicate G-Mail IDs\n");
        printf("8) Search Contact\n9) Create Favorite Contacts\n10) Display Favorite Contacts\n0) Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        getchar(); // To clear the newline character

        switch (ch) {
            case 1: display(); break;
            case 2: insert(); sort(); break;
            case 3: update(); sort(); break;
            case 4: deletecontact(); break;
            case 5: deletesamename(); break;
            case 6: deletesamenumber(); break;
            case 7: deletesamegmail(); break;
            case 8:
                printf("Search by:\n1. Name\n2. Number\n3. G-Mail\nEnter choice: ");
                scanf("%d", &ch);
                getchar();
                if (ch == 1) {
                    printf("Enter Name: ");
                    scanf(" %[^\n]", name);
                    searchbyname(name);
                } else if (ch == 2) {
                    printf("Enter Number: ");
                    scanf(" %[^\n]", number);
                    searchbynumber(number);
                } else if (ch == 3) {
                    printf("Enter G-Mail: ");
                    scanf(" %[^\n]", gmail);
                    searchbygmail(gmail);
                } else {
                    printf("Invalid choice.\n");
                }
                break;
            case 9: createFav(); break;
            case 10: displayFav(); break;
            case 0: exit(0);
            default: printf("Invalid choice.\n");
        }
    }
    return 0;
}
