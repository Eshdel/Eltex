#include <stdio.h>
#include <string.h>

#define MAX_CONTACTS 100
#define MAX_NAME_LENGTH 50
#define MAX_JOB_LENGTH 50
#define MAX_PHONE_LENGTH 20
#define MAX_EMAIL_LENGTH 50
#define MAX_SOCIAL_LENGTH 50
#define MAX_MESSENGERS_COUNT 20
#define MAX_MESSENGER_LENGTH 50
#define MAX_MESSENGER_LINK_LENGTH 50

typedef struct PersonInfo {
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];
} PersonInfo;

typedef struct WorkInfo {
    char workPlace[MAX_JOB_LENGTH];
    char job[MAX_JOB_LENGTH];
} WorkInfo;

typedef struct SocialInfo {
    char name[MAX_MESSENGER_LENGTH];
    char link[MAX_MESSENGER_LINK_LENGTH];
} SocialInfo;

typedef struct CommunicationInfo {
    int socialCount;
    char email[MAX_EMAIL_LENGTH];
    char phoneNumber[MAX_PHONE_LENGTH];
    SocialInfo social[MAX_MESSENGERS_COUNT];
} CommunicationInfo;

typedef struct Contact
{
    PersonInfo personInfo;
    WorkInfo workInfo;
    CommunicationInfo communicationInfo;
} Contact;

Contact contacts[MAX_CONTACTS];
int contactsCount = 0;

void addContact() {
    if (contactsCount < MAX_CONTACTS) {
        Contact newContact;
        printf("Enter first name: ");
        fgets(newContact.personInfo.firstName, MAX_NAME_LENGTH, stdin);
        newContact.personInfo.firstName[strcspn(newContact.personInfo.firstName, "\n")] = 0; 
        
        printf("Enter last name: ");
        fgets(newContact.personInfo.lastName, MAX_NAME_LENGTH, stdin);
        newContact.personInfo.lastName[strcspn(newContact.personInfo.lastName, "\n")] = 0; 
        
        printf("Enter work place (optional, press Enter to skip): ");
        fgets(newContact.workInfo.workPlace, MAX_JOB_LENGTH, stdin);
        newContact.workInfo.workPlace[strcspn(newContact.workInfo.workPlace, "\n")] = 0;
        
        printf("Enter job (optional, press Enter to skip): ");
        fgets(newContact.workInfo.job, MAX_JOB_LENGTH, stdin);
        newContact.workInfo.job[strcspn(newContact.workInfo.job, "\n")] = 0; 
        
        printf("Enter email (optional, press Enter to skip): ");
        fgets(newContact.communicationInfo.email, MAX_EMAIL_LENGTH, stdin);
        newContact.communicationInfo.email[strcspn(newContact.communicationInfo.email, "\n")] = 0;
        
        printf("Enter phone number (optional, press Enter to skip): ");
        fgets(newContact.communicationInfo.phoneNumber, MAX_PHONE_LENGTH, stdin);
        newContact.communicationInfo.phoneNumber[strcspn(newContact.communicationInfo.phoneNumber, "\n")] = 0;
        
        newContact.communicationInfo.socialCount = 0;

        for (int i = 0; i < MAX_MESSENGERS_COUNT; i++) {
            printf("Enter social network name (optional, press Enter to skip): ");
            fgets(newContact.communicationInfo.social[i].name, MAX_MESSENGER_LENGTH, stdin);
            newContact.communicationInfo.social[i].name[strcspn(newContact.communicationInfo.social[i].name, "\n")] = '\0'; // Remove newline character
            
            if (strlen(newContact.communicationInfo.social[i].name) == 0) {
                break;
            }
            
            printf("Enter link for %s (optional, press Enter to skip): ", newContact.communicationInfo.social[i].name);
            fgets(newContact.communicationInfo.social[i].link, MAX_MESSENGER_LINK_LENGTH, stdin);
            newContact.communicationInfo.social[i].link[strcspn(newContact.communicationInfo.social[i].link, "\n")] = '\0'; // Remove newline character
            newContact.communicationInfo.socialCount += 1;
        }

        contacts[contactsCount++] = newContact;
        printf("Contact added successfully.\n");
    } else {
        printf("Contact list is full.\n");
    }
}

void displayContacts() {
    printf("Contacts:\n");
    for (int i = 0; i < contactsCount; i++) {
        printf("%d. Name: %s %s\n", i+1, contacts[i].personInfo.firstName, contacts[i].personInfo.lastName);
        printf("   Work Place: %s\n", contacts[i].workInfo.workPlace);
        printf("   Job: %s\n", contacts[i].workInfo.job);
        printf("   Email: %s\n", contacts[i].communicationInfo.email);
        printf("   Phone Number: %s\n", contacts[i].communicationInfo.phoneNumber);
        printf("Social Networks:\n");
        for (int j = 0; j < contacts[i].communicationInfo.socialCount; j++) {
            if (strlen(contacts[i].communicationInfo.social[j].name) > 0) {
                printf("   %s: %s\n", contacts[i].communicationInfo.social[j].name, contacts[i].communicationInfo.social[j].link);
            }
        }

        printf("\n");
    }
}

void editContact() {
    int index;
    printf("Enter the index of the contact you want to edit: ");
    scanf("%d", &index);
    index--;
    
    if (index >= 0 && index < contactsCount) {
        Contact *contact = &contacts[index];
        printf("Enter first name: ");
        fgets(contact->personInfo.firstName, MAX_NAME_LENGTH, stdin);
        contact->personInfo.firstName[strcspn(contact->personInfo.firstName, "\n")] = 0; 
        
        printf("Enter last name: ");
        fgets(contact->personInfo.lastName, MAX_NAME_LENGTH, stdin);
        contact->personInfo.lastName[strcspn(contact->personInfo.lastName, "\n")] = 0; 
        
        printf("Enter work place (optional, press Enter to skip): ");
        fgets(contact->workInfo.workPlace, MAX_JOB_LENGTH, stdin);
        contact->workInfo.workPlace[strcspn(contact->workInfo.workPlace, "\n")] = 0; 
        
        printf("Enter job (optional, press Enter to skip): ");
        fgets(contact->workInfo.job, MAX_JOB_LENGTH, stdin);
        contact->workInfo.job[strcspn(contact->workInfo.job, "\n")] = 0; 
        
        printf("Enter email (optional, press Enter to skip): ");
        fgets(contact->communicationInfo.email, MAX_EMAIL_LENGTH, stdin);
        contact->communicationInfo.email[strcspn(contact->communicationInfo.email, "\n")] = 0; 

        printf("Enter phone number (optional, press Enter to skip): ");
        fgets(contact->communicationInfo.phoneNumber, MAX_PHONE_LENGTH, stdin);
        contact->communicationInfo.phoneNumber[strcspn(contact->communicationInfo.phoneNumber, "\n")] = 0; 

        printf("Do you want to edit social network information? (1 for Yes, 0 for No): ");
        int editSocial;
        scanf("%d", &editSocial);
        if (editSocial == 1) {
            editSocialInfo(contact);
        }

        printf("Contact edited successfully.\n");
    } else {
        printf("Invalid index.\n");
    }
}

void deleteContact() {
    int index;
    printf("Enter the index of the contact you want to delete: ");
    scanf("%d", &index);
    index--;

    if (index >= 0 && index < contactsCount) {
        for (int i = index; i < contactsCount - 1; i++) {
            contacts[i] = contacts[i + 1];
        }
        contactsCount--;
        printf("Contact deleted successfully.\n");
    } else {
        printf("Invalid index.\n");
    }
}

void editSocialInfo(Contact *contact) {
    int choice;
    printf("Social Networks:\n");
    for (int i = 0; i < MAX_MESSENGERS_COUNT; i++) {
        if (strlen(contact->communicationInfo.social[i].name) > 0) {
            printf("%d. %s: %s\n", i+1, contact->communicationInfo.social[i].name, contact->communicationInfo.social[i].link);
        }
    }
    printf("Enter the number of the social network you want to edit (0 to cancel): ");
    scanf("%d", &choice);
    if (choice >= 1 && choice <= MAX_MESSENGERS_COUNT) {
        choice--;
        printf("Enter new social network name: ");
        fgets(contact->communicationInfo.social[choice].name, MAX_MESSENGER_LENGTH, stdin);
        contact->communicationInfo.social[choice].name[strcspn(contact->communicationInfo.social[choice].name, "\n")] = '\0'; // Remove newline character

        printf("Enter new link: ");
        fgets(contact->communicationInfo.social[choice].link, MAX_MESSENGER_LINK_LENGTH, stdin);
        contact->communicationInfo.social[choice].link[strcspn(contact->communicationInfo.social[choice].link, "\n")] = '\0'; // Remove newline character
    }
    else if (choice != 0)
        printf("Invalid choice.\n");
}

int main() {
    int choice;
    do {
        printf("\n Menu:\n");
        printf("1. Add Contact\n");
        printf("2. Display Contacts\n");
        printf("3. Edit Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addContact();
                break;
            case 2:
                displayContacts();
                break;
            case 3:
                editContact();
                break;
            case 4:
                deleteContact();
                break;
            case 5:
                printf("Exit\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}