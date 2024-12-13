#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    char phone[15];
    char email[50];
} Contact;

void AddContact();
void DeletContact();
void SearchByName();
void SearchByPhoneNumber();
void SearchByEmail();
void SortContacts(Contact* contacts, int count);
void SeeContacts();
void WriteContactsToFile(Contact* contacts, int count);
int ReadContactsFromFile(Contact* contacts);

int main() {
    int choice;
    do
    {
        printf("1. Add Contatc\n");
        printf("2. Delete Contatc\n");
        printf("3. Search By Name\n");
        printf("4. Search By Phone Number\n");
        printf("5. Search By Email\n");
        printf("6. See Contacts\n");
        printf("7. Exit\n");
        printf("Enter Your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
        case 1: 
            AddContact();
        break;
        case 2:
            DeletContact();
        break;
        case 3: 
            SearchByName();
        break;
        case 4:
            SearchByPhoneNumber();
        break;
        case 5: 
            SearchByEmail();
        break;
        case 6:
            SeeContacts();
        break;
        case 7:
            printf("Exiting...");
            break;
        default:
            printf("Invalid choice. Please try again.");
        }
    } while (choice != 7);

    return 0;
}

                                        //////////////////   Add  Contact     /////////////////////
void AddContact() {
    Contact newContact;
    printf("Enter Name: ");
    fgets(newContact.name, 50, stdin);
    newContact.name[strcspn(newContact.name, "\n")] = '\0';

    printf("Enter Phone Number: ");
    fgets(newContact.phone, 15, stdin);
    newContact.phone[strcspn(newContact.phone, "\n")] = '\0';

    printf("Enter Email: ");
    fgets(newContact.email, 50, stdin);
    newContact.email[strcspn(newContact.email, "\n")] = '\0';

    Contact contacts[100];
    int count = ReadContactsFromFile(contacts);
    contacts[count++] = newContact;

    SortContacts(contacts, count);
    WriteContactsToFile(contacts, count);

    printf("Contact added successfully!\n");
}

                                        //////////////////   Delete Contact      //////////////////
void DeletContact() {
    char name[50];
    printf("Enter the name of the contact to delete: ");
    fgets(name, 50, stdin);
    name[strcspn(name, "\n")] = '\0';

    Contact contacts[100];
    int count = ReadContactsFromFile(contacts);

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(contacts[i].name, name) == 0) {
            for (int j = i; j < count - 1; j++) {
                contacts[j] = contacts[j+1];
            }
            count--;
            found = 1;
            break;
        }
    }

    if (found) {
        SortContacts(contacts, count);
        WriteContactsToFile(contacts, count);
        printf("Contact deleted successfully!\n");
    } else {
        printf("Contact not found.\n");
    }
    
}

                                        //////////////////   Search by Name       //////////////////
void SearchByName() {
    char name[50];
    printf("Enter the name to search\n");
    fgets(name, 50, stdin);
    name[strcspn(name, "\n")] = '\0';

    Contact contacts[100];
    int count = ReadContactsFromFile(contacts);
    for (int i = 0; i < count; i++) {
        if (strcmp(contacts[i].name, name) == 0) {
            printf("Name: %s\nPhone: %s\nEmail: %s\n", contacts[i].name, contacts[i].phone, contacts[i].email);
            return;
        }
    }
    printf("Contact not found.\n");
}

                                        //////////////////   Search By Phone Number    /////////////
void SearchByPhoneNumber() {
    char phone[15];
    printf("Enter the phone number to search\n");
    fgets(phone, 15, stdin);
    phone[strcspn(phone, "\n")] = '\0';

    Contact contacts[100];
    int count = ReadContactsFromFile(contacts);
    for (int i = 0; i < count; i++) {
        if (strcmp(contacts[i].phone, phone) == 0) {
            printf("Name: %s\nPhone: %s\nEmail: %s\n", contacts[i].name, contacts[i].phone, contacts[i].email);
            return;
        }
    }
    printf("Contact not found.\n");
}

                                        //////////////////   Search by Email       //////////////////
void SearchByEmail() {
    char email[50];
    printf("Enter the email to search\n");
    fgets(email, 50, stdin);
    email[strcspn(email, "\n")] = '\0';

    Contact contacts[100];
    int count  = ReadContactsFromFile(contacts);
    for (int i = 0; i < count; i++) {
        if (strcmp(contacts[i].email, email) == 0) {
            printf("Name: %s\nPhone: %s\nEmail: %s\n", contacts[i].name, contacts[i].phone, contacts[i].email);
            return;
        }
    }
    printf("Contact not found\n");
}

                                        //////////////////   Sort Contacts      /////////////////////
void SortContacts(Contact* contacts, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcasecmp(contacts[j].name, contacts[j+1].name) > 0) { // if equal 0 the strings are equal
                Contact temp = contacts[j];
                contacts[j] = contacts[j+1];
                contacts[j+1] = temp;
            }   
        }   
    }
}

                                        //////////////////   Display Contacts      //////////////////
void SeeContacts() {
    Contact contacts[100];
    int count = ReadContactsFromFile(contacts);

    if (count == 0) {
        printf("No contacts found.\n");
        return;
    }

    printf("Contacts:\n");
    for (int i = 0; i < count; i++) {
        printf("Name: %s\nPhone: %s\nEmail: %s\n", contacts[i].name, contacts[i].phone, contacts[i].email);
    }
    
    
}

                                        //////////////////   Write contacts to File     /////////////
void WriteContactsToFile(Contact* contacts, int count) {
    FILE* file = fopen("program.txt", "w"); 
    if (!file) {
        perror("Failed to open file\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s\n%s\n%s\n", contacts[i].name, contacts[i].phone, contacts[i].email);
    }
    
    fclose(file);
}


                                        //////////////////   Read contacts from File     ////////////
int ReadContactsFromFile(Contact* contacts) {
    FILE* file = fopen("program.txt", "r");
    if (!file) {
        perror("Failed to open file\n");
        return 0;
    }
    int count = 0;
    while (fgets(contacts[count].name, 50, file)) {
        fgets(contacts[count].phone, 15, file);
        fgets(contacts[count].email, 50, file);

        contacts[count].name[strcspn(contacts[count].name, "\n")] = '\0';
        contacts[count].phone[strcspn(contacts[count].phone, "\n")] = '\0';
        contacts[count].email[strcspn(contacts[count].email, "\n")] = '\0';
        
        count++;
    }

    fclose(file);
    return count;
}
