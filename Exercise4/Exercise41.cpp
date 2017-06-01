/// Νικόλαος Παναγιώτης Κούκουρας ICSD-2014093
/// Γέροντας Αλέξανδρος ICSD-2015029

#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>
using namespace std;

struct node /// Λίστα για την αποθήκευση των αριθμών γραμμής που εμφανίζεται η λέξη.
{
    int line;
    node* next = NULL;

    node(int itsLine)
    {
        line = itsLine;
    }
};

struct tree /// Δυαδικό δέντρο αναζήτησης για την υλοποίηση του ευρετηρίου.
{
    string word;
    tree* left,*right,*par;
    node* head;

    tree(string word,tree* par = NULL,int line = 1) /// Constructor δυαδικού δέντρου.
    {
        left = NULL;
        right = NULL;
        par = NULL;

        head = new node(line);
        this->word = word;
        this->par = par;
    }

    void addNode(int line, node *tempNode = NULL) /// Πρόσθεση γραμμής στην λίστα.
    {
        if (!tempNode) tempNode = head;
        if (!tempNode->next) tempNode->next = new node(line);
        else addNode(line,tempNode->next);
    }
};

int countNode(node* tempNode) /// Mετρητής κόμβων της λίστας.
{
    int count = 1;
    if (tempNode->next) count += countNode(tempNode->next); /// Aναδρομή για το μετρημα ολων των κομβων.
    return count;
}

void printNode(node* tempNode) /// Τύπωση τιμής κόμβου της λίστας.
{
    cout << tempNode->line;
    if (tempNode->next) cout << ", ", printNode(tempNode->next); /// Αναδρομή μέχρι να τυπωθούν οι τιμές όλων των κόμβων.
}

bool searchLine(node* headNode,int line) /// Aναζήτηση συγκεκριμένης γραμμής στην λίστα.
{
    /// Aναδρομή στον επόμενο κόμβο της λίστας μέχρι να βρεθεί η γραμμή που αναζητείται.
    if (headNode->line < line && headNode->next) return searchLine(headNode->next,line);
    return (headNode->line == line);
}

void inOrder(tree* root) /// Ενδοδιατεταγμένη διάσχιση του δέντρου.
{
    if (!root) return;
    inOrder(root->left); /// Aναδρομή για την τυπωση του αριστερού κλαδιού.
    cout << "\n" << root->word << " : "; /// Τύπωση λέξης.
    printNode(root->head); /// Τύπωση των γραμμών στις οποίες εμφανίζεται η λέξη.
    inOrder(root->right); /// Aναδρομή για την τυπωση του δεξιού κλαδιού.
}

tree *searchWord(tree *leaf, string word) /// Αναζήτηση Λέξης στο δυαδικό δέντρο.
{
    /// Συγκρίνοντας την λέξη που ψάχνουμε με την λέξη στον κόμβο,
    /// κινούμαστε αναδρομικά στο αριστερό η δεξί παιδί του.
    if (leaf && word.compare(leaf->word) < 0) leaf = searchWord(leaf->left,word);
    else if (leaf && word.compare(leaf->word) > 0) leaf = searchWord(leaf->right,word);

    if (!leaf) return 0; /// Αν ο κόμβος δεν βρέθηκε επιστρέφεται null.
    if  (word == leaf->word) return leaf; /// Aλλιώς επιστρέφεται ο κόμβος.
}

tree* predecessor(tree* leaf) /// Aλγόριθμος εύρεσης του προηγούμενου στοιχείου.
{
    /// Aν το leaf έχει αριστερό υπόδεντρο τότε επέλεξε το δεξιότερο κόμβο στο αριστερό υπόδεντρο.
    tree* leafNode = leaf->left;

    while(leafNode)
    {
        if (!leafNode->right) return leafNode;
        leafNode = leafNode->right;
    }

    /// Διαφορετικά, επέλεξε στο μονοπάτι προς τη ρίζα τον πρώτο γονέα με δεξί παιδί πρόγονο του leaf.
    leafNode = leaf->par;

    while (leafNode && (leaf == leafNode->left))
    {
        leaf = leafNode;
        leafNode = leaf->par;
    }
    return leafNode;
}

void insertLeaf(tree *leaf, string word,int line)
{
    /// Συγκρίνοντας την λέξη που θέλουμε να εισάγουμε με την λέξη στον κόμβο,
    /// κινούμαστε αναδρομικά στο αριστερό η δεξί παιδί του.
    if (word.compare(leaf->word) < 0)
    {
        if (!leaf->left) leaf->left = new tree(word,leaf,line); /// Αν τo παιδί του κόμβου είναι null-φύλλο
        else insertLeaf(leaf->left,word,line);                  /// εισάγουμε την λέξη σε αυτό. Αλλιώς κάνουμε
    }                                                           /// αναδρομή μέχρι να βρούμε null-φύλλο.

    else if (word.compare(leaf->word) > 0)
    {
        if (!leaf->right) leaf->right = new tree(word,leaf,line);
        else insertLeaf(leaf->right,word,line);
    }
}

void deleteLeaf(tree*& root, string word) /// Διαγραφή κόμβου από το δένρο.
{
    tree* leaf = searchWord(root,word); /// Εύρεση του κόμβου με χρήση της searchWord.
    tree* parTree = leaf->par;          /// Πατέρας του κόμβου.

    if (!leaf->left && !leaf->right) /// Aν ο κόμβος έχει παιδιά null φύλλα, διαγράφεται χωρίς άλλες ενέργιες.
    {
        if (parTree && parTree->left == leaf) parTree->left = NULL;
        else if (parTree && parTree->right == leaf) parTree->right = NULL;
        if (leaf == root) root = NULL;
    }

    else if (leaf->left && leaf->right) /// Aν ο κόμβος έχει 2 παιδιά.
    {
        string word = predecessor(leaf)->word; /// Αποθήκευση τιμών του προηγούμενου στοιχείου
        node* tempHead = predecessor(leaf)->head; /// σε προσωρινές μεταβλητές.

        deleteLeaf(root,word); /// Διαγραφή του προηγούμενου στοιχείου.

        leaf->word = word; /// Ο κόμβος παίρνει της τιμές του προηγούμενου στοιχείου.
        leaf->head = tempHead;
    }

    else if (!leaf->left || !leaf->right) /// Aν ο κόμβος έχει ένα παιδί.
    {
        if (leaf->left) *leaf = *leaf->left; /// Το παιδί παίρνει την θέση του κόμβου.
        else if (leaf->right) *leaf = *leaf->right;

        leaf->par = parTree;                /// Ο καινούριος κόμβος πρέπει να δείχνει στον πατέρα του κόμβου που διαγράφτηκε
        if (leaf->left) leaf->left->par = leaf; /// και τα παιδιά του καινούριου κόμβου να δείχνουν σε αυτόν.
        if (leaf->right) leaf->right->par = leaf;
    }
}

class wordIndex
{
private:                          /// Στον μετρητή discreteWords καταχωρείται το σύνολο των διακριτών λέξεων στο ευρετήριο
    int discreteWords,indexWords; /// ενω στον indexWords, το πλήθος των διακριτών λέξεων.
    tree* root = NULL;
    double msecs;

public:
    void createIndex() /// Διάβασμα του αρχείου και καταχώρηση λέξεων στο ευρετήριο.
    {
        discreteWords = 0;
        indexWords = 0;
        int line = 1;
        ifstream file;
        string tempString,word;

        while (!file.is_open()) /// Εισαγωγή ονόματος αρχείου.
        {
            cout << "eisagogi onomatos arxeiou:";
            cin >> tempString;
            file.open(tempString.c_str());
        }

        clock_t time = clock();

        while (file >> tempString)
        {
            word="";

            remove_copy_if(tempString.begin(), tempString.end(),back_inserter(word),
                           ptr_fun<int, int>(&ispunct) ); /// Αφαίρεση σημείων στίξης.

            /// Mετατροπή των γραμμάτων της λέξης σε κεφαλαία.
            transform(word.begin(), word.end(),word.begin(), ::toupper);

            /// Αν η λέξη δεν υπάρχει στο δυαδικό δέντρο, καταχωρείται νέος κόμβος με την λέξη και μια γραμμική λιστα με την γραμμή στην οποία βρίσκεται.
            /// Αν η λέξη υπάρχει ήδη στο δυαδικό δέντρο, ενημερώνεται η λίστα με την γραμμή στην οποία ξαναεμφανιζεται η λέξη.
            if (!root) root = new tree(word),discreteWords++; /// Αρχικοποίηση του δυαδικού δέντρου.
            else if (!searchWord(root,word)) insertLeaf(root,word,line),discreteWords++;
            else if (!searchLine(searchWord(root,word)->head,line)) searchWord(root,word)->addNode(line),indexWords++;

            if (file.get() == '\n') line++;
        }

        msecs = ((double) (clock() - time)) / CLOCKS_PER_SEC; /// Υπολογισμός χρόνου για την κατασκευή του δυαδικού δέντρου.
        file.close(); /// Kλείσιμο αρχείου.
    }

    void userInput() /// Εισαγωγή λέξης από τον χρήστη.
    {
        string word;
        int wordLine;

        cout << "dose mia leksi pou thes na eisageis kai tin grammi stin opoia brisketai: ";
        cin >> word >> wordLine;

        transform(word.begin(), word.end(),word.begin(), ::toupper);

        if (!root) root = new tree(word),discreteWords++;
        else if (!searchWord(root,word)) insertLeaf(root,word,wordLine),discreteWords++;
        else if (!searchLine(searchWord(root,word)->head,wordLine)) searchWord(root,word)->addNode(wordLine),indexWords++;
        else cout << "i leksi einai idi kataxorimeni\n\n";
    }

    void deleteIndexWord() /// Ο χρήστης εισάγει την λέξη που θέλει να διαγράψει.
    {
        string word;

        cout << "dose tin leksi pou thes na diagrapsis: ";
        cin >> word;

        if (searchWord(root,word)) /// Η deleteLeaf καλείται μόνο αν η λέξη υπάρχει.
        {
            discreteWords--; /// Ενημέρωση μετρητών.
            /// Xρήση της countNode για να μετρησουμε τις γραμμές που εμφανίστηκε η λέξη.
            indexWords -= countNode(searchWord(root,word)->head) - 1;
            deleteLeaf(root,word),cout << "i leksi diagraftike\n\n";
        }
        else cout << "i leksi dn iparxei\n\n";
    }

    void printIndex() /// Εμφάνιση ολόκληρου του ευρετηρίου.
    {
        cout << "Euretirio Lekseon:\n----------------------------------------";
        inOrder(root);
        cout << "\n\nSinolikos arithmos lekseon keimenou: " << discreteWords + indexWords << endl;
        cout << "Arithmos Lekseon Euretiriou: " << discreteWords << endl;

        cout << "Xronos pou xreiastike gia tin dimiourgia tou diadikou dentrou anazitisis einai : "
             << msecs << " sec." << endl << endl;
    }

    void exportIndex() /// Καταχώρηση ευρετηρίου στο αρχείο index_bst.
    {
        freopen("index_bst.txt", "w", stdout); /// Ανακατεύθυνση της ροής εξόδου στο αρχείο index_bst.
        printIndex(); /// Το ευρετήριο θα αποθηκευτεί στο αρχείο αντί να εμφανιστεί στην οθόνη.
        fclose (stdout);
    }
};

int main()
{
    wordIndex *index = new wordIndex;
    index->createIndex();
    int choice = -1;

    while(choice != 0)
    {
        cout << "1.tiposi apotelesmaton\n";
        cout << "2.kataxorisi leksis.\n";
        cout << "3.diagrafi leksis\n";
        cout << "0.eksodos.\nepilogi: ";
        cin >> choice;

        if (choice == 1) index->printIndex();
        if (choice == 2) index->userInput();
        if (choice == 3) index->deleteIndexWord();
        if (choice == 0) break;
    }

    index->exportIndex();
    return 0;
}
