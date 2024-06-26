
struct Node {
    private:
        // indicates if a string ends with this character
        int words = 0;
        int prefixes = 0;

        // successors
        Node *links[26]{};

    public:
        void createSuccessor(char ch, Node *node) {
            links[ch - 'a'] = node;
        }

        bool isSuccessorExists(char ch) {
            return (links[ch - 'a'] != NULL);
        }

        Node *getSuccessor(char ch) {
            return links[ch - 'a'];
        }

        int getEnds() {
            return words;
        }

        int getPrefixes() {
            return prefixes;
        }

        void addEnd() {
            words++;
        }

        void removeEnd() {
            words--;
        }

        void addPrefix() {
            prefixes++;
        }

        void removePrefix() {
            prefixes--;
        }
};

/*
 * - you always start each iteration in all methods
 *   with later trie node than word character by 1
 * */
class Trie {
    private:
        Node* root;
    public:
        // بداية التفريعة
        Trie() {
            root = new Node();
        }

        void insert(string word) {
            Node *node = root;
            for (int i = 0; i < word.size(); i++) {
                if (!node -> isSuccessorExists(word[i])) node -> createSuccessor(word[i], new Node());
                node = node -> getSuccessor(word[i]);
                node -> addPrefix();
            }
            node -> addEnd();
        }

        bool search(string word) {
            Node *node = root;
            for (int i = 0; i < word.size(); node = node -> getSuccessor(word[i]), i++) {
                if (!node -> isSuccessorExists(word[i])) return false;
            }
            return node -> getEnds();
        }

        int countWordsEqualTo(string &word) {
            Node *node = root;
            for (int i = 0; i < word.length(); i++) {
                if (node -> isSuccessorExists(word[i])) node = node -> getSuccessor(word[i]);
                else return 0;
            }
            return node -> getEnds();
        }


        int countWordsStartingWith(string &word) {
            Node *node = root;
            for (int i = 0; i < word.length(); i++) {
                if (node -> isSuccessorExists(word[i])) node = node -> getSuccessor(word[i]);
                else return 0;
            }
            return node -> getPrefixes();
        }

        // assumes that you'll never erase non-existing words
        void erase(string &word) {
            Node * node = root;
            for (int i = 0; i < word.length(); i++) {
                node = node -> getSuccessor(word[i]);
                node -> removePrefix();
            }
            node -> removeEnd();
        }
};
