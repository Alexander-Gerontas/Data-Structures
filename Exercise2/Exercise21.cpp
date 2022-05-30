// Αλέξανδρος Γέροντας - ICSD15029

#include <iostream>

struct Node
{
    Node *next = NULL;
    Node *prev = NULL;
    int value;
};

// Συνάρτηση -1-
void addNodeSingle(Node **head, int value, int pos) {
    Node *current = new Node;

    current->value = value;

    if (pos == 0) {
        current->next = *head;
        *head = current;
    }

    if (pos == 1) {
        // Το headNode χρειάζεται διότι το head, έγινε pass by reference
        Node *headNode = *head;

        if (headNode != NULL) {
            // Επειδή είναι Single Linked, διασχίζουμε την λίστα
            while (headNode->next != NULL)
                headNode = headNode->next;

            headNode->next = current;
        }

        // Σε περίπτωση που θέλουμε να μπούνε όλες οι τιμές με pos=1
        else *head = current;
    }
}

// Συνάρτηση -2-
void addAscending(Node **head, int value) {
    Node *current = new Node;
    Node *headNode = *head, *nodeBefore = NULL;

    // Διασχίζει την λίστα όσο ο αριθμός του κόμβου ειναι μικρότερος.
    while (headNode != NULL) {
        if (headNode->value < value) {
            nodeBefore = headNode;
            headNode = headNode->next;
        }

        else break;
    }

    current->value = value;
    current->next = headNode;

    // Ελέγχει την περίπτωση που ο αριθμός είναι μικρότερος του head.
    if (nodeBefore != NULL) nodeBefore->next = current;
    else *head = current;
}

// Συνάρτηση -3-
int countList(Node *head) {
    int nodes=0;

    if (head == NULL) return 0;

    // Μέτρηση κόμβων
    while (head != NULL) {
        nodes++;
        head=head->next;
    }

    return nodes;
}

// Συνάρτηση -4-
void displayList(Node *head) {

    // Διάσχηση λίστας
    while (head != NULL) {
        std::cout << head->value << " ";
        head = head->next;
    }

    std::cout << std::endl;
}

// Συνάρτηση -5-
void deleteFirst(Node **head) {
    Node *firstPos = *head;

    *head = (*head)->next;
    delete firstPos;
}

// Συνάρτηση -6-
void deleteNode(Node **head, int value) {
    Node *headNode = *head, *nodeBefore = NULL;

    // Στον πρώτο κόμβο, το nodeBefore είναι ακόμα NULL
    if (headNode->value == value) deleteFirst(head);

    else while (headNode != NULL) {
        if (headNode->value == value) {
            // Όταν βρεθεί θέτουμε τα νέα next και τον διαγράφουμε
            nodeBefore->next = headNode->next;

            delete headNode;
            break;
        } else {
            // Το χρειαζόμαστε επειδή δεν υπάρχει δείκτης prev
            nodeBefore = headNode;

            headNode = headNode->next;
        }
    }
}

// Συνάρτηση -7-
Node* appendLists(Node **head, Node **secHead) {
    Node *fHead = *head, *sHead = *secHead, *appHead = NULL;

    // Έλενχος αν έχουν εισαχθεί όλα τα στοιχεία
    while (fHead != NULL || sHead != NULL) {
        // Σύγκριση στοιχείων και εισαγωγή του μεγαλύτερου αριθμού
        // Σε περίπτωση όπου έχουν περαστεί όλα τα στοιχεία μιας λίστας εισάγωνται τα στοιχεία τις δεύτερης λίστας.
        if ( sHead == NULL || (fHead != NULL && fHead->value < sHead->value) ) {
            addNodeSingle(&appHead, fHead->value, 1);
            fHead = fHead->next;
        } else {
            addNodeSingle(&appHead, sHead->value, 1);
            sHead = sHead->next;
        }
    }

    return appHead;
}

// Συνάρτηση -8-
void addNodeDouble(Node **head, Node **tail, int value, int pos) {
    Node *current = new Node;

    current->value = value;

    if (pos == 0) {
        current->next = *head;

        if (*head != NULL) (*head)->prev = current;

        // Χρειάζεται, αν θέλουμε μετά την pos=0, να καλέσουμε και pos=1
        else *tail = current;

        *head = current;
    }

    if (pos == 1) {
        if (*head != NULL) (*tail)->next = current;

        current->prev = *tail;
        *tail = current;

        // Σε περίπτωση που θέλουμε να μπουνε όλες οι τιμές με pos=1
        if (*head == NULL) *head = *tail;
    }
}

// Συνάρτηση -9-
void reversedisplayList(Node *head, Node *tail) {
    // Αντί για head->prev θα μπορούσε να μπει NULL, όμως ζητείται το head.
    while (tail != head->prev) {
        std::cout << tail->value << " ";
        tail = tail->prev;
    }

    std::cout << std::endl;
}

// Συνάρτηση -10-
void swapElements1(Node **head) {
    Node *headNode = *head;
    int temp;

    while ( (headNode->next != NULL) )
        headNode = headNode->next;

    // Ανταλλαγή τιμών
    temp = (*head)->value;
    (*head)->value = headNode->value;
    headNode->value = temp;
}

// Συνάρτηση -11-
void swapElements2(Node **head, Node **tail) {
    int temp = (*head)->value;

    // Ανταλλαγή τιμών
    (*head)->value = (*tail)->value;
    (*tail)->value = temp;
}

// Συνάρτηση -12-
void swapElements3(Node **head) {
    Node *headNode = *head;
    int temp = (*head)->value;

    while (headNode->next != *head)
        headNode = headNode->next;

    // Ανταλλαγή τιμών
    (*head)->value = headNode->value;
    headNode->value = temp;
}

// Μετατρέπει μία απλά διασυνδεμένη λίστα σε κυκλική
void convertToCircular (Node *head) {
    Node *headNode = head;

    while (headNode->next != NULL)
        headNode = headNode->next;

    headNode->next = head;
}

// Χρειάζεται για την επίδειξη της ορθής λειτουργίας μιας κυκλικής λίστας
void displayCircular (Node *head) {
    Node *headNode = head;

    while (headNode->next != head) {
        std::cout << headNode->value << " ";
        headNode = headNode->next;
    }

    //Στον βρόγχο δεν συμπεριλαμβάνεται η τελική τιμή
    std::cout << headNode->value << std::endl;
}

int main() {
    Node *head = NULL, *secHead = NULL, *appHead = NULL;
    Node *dlHead = NULL, *tail = NULL;

    for (int i=0; i<10; i++) {
        if (i==0) addNodeSingle(&head, i, 0);
        if (i!=0 && i!=5) addNodeSingle(&head, i, 1);
    }

    std::cout << "1. AddNodeSingle me 9 kombous: ";
    displayList(head);

    std::cout << "2. addAscending me timi to 5: ";
    addAscending(&head, 5);
    displayList(head);

    std::cout << "3. countList tis listas: " << countList(head) << std::endl;
    std::cout << "4. displayList - Xrisimopoihthike." << std::endl;

    std::cout << "5. deleteFirst tis listas: ";
    deleteFirst(&head);
    displayList(head);

    std::cout << "6. deleteNode me timi to 9: ";
    deleteNode(&head, 9);
    displayList(head);

    for (int i=0; i<10; i++) {
        if (i==0) addNodeSingle(&secHead, i, 0);
        if (i!=0) addNodeSingle(&secHead, i, 1);
    }

    std::cout << "7. appendLists tis proigoumenis me nea." << std::endl;
    appHead = appendLists(&head, &secHead);

    std::cout << "Nea: ";
    displayList(secHead);

    std::cout << "Sinenomeni: ";
    displayList(appHead);

    for (int i=0; i<10; i++) {
        if (i==0) addNodeDouble(&dlHead, &tail, i, 0);
        if (i!=0) addNodeDouble(&dlHead, &tail, i, 1);
    }

    std::cout << "8. addNodeDouble me 10 kombous tupomenous anapoda: ";
    reversedisplayList(dlHead, tail);

    std::cout << "9. reversedisplayList - Xrisimopoiithike." << std::endl;

    std::cout << "10. swapElements1 tis sunenomenis: ";
    swapElements1(&appHead);
    displayList(appHead);

    std::cout << "11. swapElements2 dipla diasindemenis listas, anapoda: ";
    swapElements2(&dlHead, &tail);
    reversedisplayList(dlHead, tail);

    std::cout << "12. swapElements3 tis sinenomenis, metatremeni se kikliki: ";
    convertToCircular(appHead);
    swapElements3(&appHead);
    displayCircular(appHead);

    return 0;
}
