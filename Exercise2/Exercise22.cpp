// Αλέξανδρος Γέροντας - ICSD15029

#include <iostream>

struct Data {
    double popularity;
    std::string title, author, description, type;
};

struct Node {
    Node *next = NULL;
    Node *prev = NULL;
    Data *data;

    Node() {
        data = new Data;
    }
};

// Έλεγχος ύπαρξης βιβλίου στην λίστα.
bool bookExists(Node **head, std::string title) {
    Node *headNode = *head;

    do if ( headNode->data->title == title) return true;
    while ((headNode = headNode->next) != NULL);

    return false;
}

// Ανταλλαγή διευθύνσεων Data, χρειάζεται στην ταξινόμηση.
void swapData(Node *headNode, Node *compNode) {
    Data* tempData = headNode->data;

    headNode->data = compNode->data;
    compNode->data = tempData;
}

// Χρεισιμοποιούμε την Bubble Sort.
void sortBooks(Node **head,Node **tail) {
    Node *headNode, *compNode;

    for (headNode = *head; headNode != *tail; headNode = headNode->next)
        for (compNode = *tail; compNode != headNode; compNode = compNode->prev) {
            if ( (headNode->data->title > compNode->data->title) && (compNode->data->popularity == headNode->data->popularity) )
                swapData(headNode, compNode);

            else if (compNode->data->popularity > headNode->data->popularity)
                swapData(headNode, compNode);
        }
}

// Προσθήκη βιβλίου.
void addBook(Node **head, Node **tail, std::string title, std::string author, std::string type, std::string description) {
    Node *current = new Node;

    if ( (*head == NULL ) || !bookExists(&*head, title) ) {
        current->data->title = title;
        current->data->author = author;
        current->data->type = type;
        current->data->description = description;
        current->data->popularity = 0;

        // Τοποθετούνται στην αρχή της λίστας, μετά ταξινομούνται.
        current->next = *head;
        if ( *head != NULL ) (*head)->prev = current;
        else  *tail = current;
        *head = current;

        sortBooks(&*head, &*tail);
    }
}

// Αναζήτηση βιβλίου.
void searchBook(Node **head, Node **tail) {
    Node *headNode = *head;
    std::string title;

    std::cout << "Titlos: ";
    std::cin >> title;

    do if (headNode->data->title == title) {
            headNode->data->popularity += 0.5;

            // Αποτελέσματα αναζήτησης.
            std::cout << "Apotelesmata:" << std::endl;
            std::cout << "Titlos: " << headNode->data->title << std::endl;
            std::cout << "Sigrapheas: " << headNode->data->author << std::endl;
            std::cout << "Typos: " << headNode->data->type << std::endl;
            std::cout << "Perigraphi: " << headNode->data->description << std::endl;
            std::cout << "Diasimotita: " << headNode->data->popularity << std::endl;

            // Ταξινομούνται με βάση την νέα δημοτικότητα.
            sortBooks(&*head, &*tail);
            break;
        }
    while  ( (headNode = headNode->next) != NULL );
}

// Διαγραφή βιβλίου.
void deleteBook(Node **head) {
    Node *headNode = *head;
    std::string title;

    std::cout << "Titlos: ";
    std::cin >> title;

    do if (headNode->data->title == title) {
            // Ενημέρωση διεθύνσεων πριν διαγραφεί ο κόμβος.
            if (headNode == *head) *head = headNode->next;
            if (headNode->prev != NULL) headNode->prev->next = headNode->next;
            if (headNode->next != NULL) headNode->next->prev = headNode->prev;

            delete headNode;
            break;
       }
    while ( (headNode = headNode->next) != NULL );
}

// Μέτρηση πλήθους βιβλίων.
void countBooks(Node **head) {
    Node *headNode = *head;
    int nodes = 1;

    if (*head == NULL) nodes = 0;
    else while ( (headNode = headNode->next) != NULL ) nodes++;

    std::cout << nodes << std::endl;
}

// Τυπώνει τα βιβλία με την μεγαλύτερη δημοτικότητα.
void mostPopularBooks(Node **head) {
    Node *headNode = *head;

    // Όσα βιβλία έχουν την δημοτικότητα του ποιο διάσημου βιβλίου (head), τότε τυπώνονται.
    if ( (*head)->data->popularity != 0 ) do std::cout << headNode->data->title << " ";
    while ( ((headNode = headNode->next) != NULL) && (headNode->data->popularity == (*head)->data->popularity) );

    std::cout << std::endl;
}

// Τυπώνει τα βιβλία με την μικρότερη δημοτικότητα.
void lessPopularBooks(Node **tail) {
    Node *tailNode = *tail;

    // Όσα βιβλία έχουν την χειρότερη δημοτικότητα (δηλ. όση του tail), τότε τυπώνονται.
    // Επειδή ξεκινάμε από το tail, τυπώνονται ανάποδα.
    do std::cout << tailNode->data->title << " ";
    while ( ((tailNode = tailNode->prev) != NULL) && (tailNode->data->popularity == (*tail)->data->popularity) );

    std::cout << std::endl;
}

// Εμφάνιση όλων των βιβλίων.
void displayBooks(Node *head) {
    Node *headNode = head;

    do std::cout << headNode->data->title << " ";
    while ( (headNode = headNode->next) != NULL );

    std::cout << std::endl;
}

int main() {
    std::string title, author, type, description;
    Node *head = NULL, *tail = NULL;

    int choice;

    // Ενδεικτικά βιβλία.
    addBook(&head, &tail, "BookA", "AuthorA", "TypeA", "DescriptionA");
    addBook(&head, &tail, "BookB", "AuthorB", "TypeB", "DescriptionB");
    addBook(&head, &tail, "BookC", "AuthorC", "TypeC", "DescriptionC");
    addBook(&head, &tail, "BookD", "AuthorD", "TypeD", "DescriptionD");
    addBook(&head, &tail, "BookE", "AuthorE", "TypeE", "DescriptionE");

    do
    {
        // Μενού.
        std::cout << "0. Eksodos." << std::endl;
        std::cout << "1. Eisagogi." << std::endl;
        std::cout << "2. Anazitisi." << std::endl;
        std::cout << "3. Diagraphi." << std::endl;
        std::cout << "4. Emfanisi Plithous." << std::endl;
        std::cout << "5. Emfanisi Diasimon." << std::endl;
        std::cout << "6. Emfanisi mi-diasimon." << std::endl;
        std::cout << "7. Emfanisi sillogis." << std::endl;

        std::cout << ">> ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Titlos: ";
                std::cin >> title;

                std::cout << "Sigrapheas: ";
                std::cin >> author;

                std::cout << "Typos: ";
                std::cin >> type;

                std::cout << "Perigraphi: ";
                std::cin >> description;

                addBook(&head, &tail, title, author, type, description);
                break;

            case 2:
                searchBook(&head,&tail);
                break;

           case 3:
                deleteBook(&head);
                break;

           case 4:
                countBooks(&head);
                break;

           case 5:
                mostPopularBooks(&head);
                break;

           case 6:
                lessPopularBooks(&tail);
                break;

           case 7:
                displayBooks(head);
                break;
        }
    } while (choice != 0);

    return 0;
}
