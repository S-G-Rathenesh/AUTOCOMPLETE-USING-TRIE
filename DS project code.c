#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#define ALPHABET_SIZE 26

// Trie node structure
typedef struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    bool isEndOfWord;
} TrieNode;

// Create a new trie node
TrieNode *createNode(void) {
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
    node->isEndOfWord = false;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }
    return node;
}

// Insert a word into the trie
void insert(TrieNode *root, const char *word) {
    TrieNode *current = root;
    while (*word) {
        int index = tolower(*word) - 'a';
        if (!current->children[index]) {
            current->children[index] = createNode();
        }
        current = current->children[index];
        word++;
    }
    current->isEndOfWord = true;
}

// Helper function for autocomplete
void autocompleteHelper(TrieNode *current, char *buffer, int level) {
    if (current->isEndOfWord) {
        buffer[level] = '\0';
        printf("%s\n", buffer);
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (current->children[i]) {
            buffer[level] = i + 'a';
            autocompleteHelper(current->children[i], buffer, level + 1);
        }
    }
}

// Autocomplete function
void autocomplete(TrieNode *root, const char *prefix) {
    TrieNode *current = root;
    while (*prefix) {
        int index = tolower(*prefix) - 'a';
        if (!current->children[index]) {
            printf("No suggestions found for \"%s\"\n", prefix);
            return;
        }
        current = current->children[index];
        prefix++;
    }
    char buffer[100];
    strncpy(buffer, prefix, strlen(prefix));
    autocompleteHelper(current, buffer, strlen(prefix));
}

int main() {
    TrieNode *root = createNode();

    // List of words
    const char *words[] = {
        "Apple", "Ant", "Art", "Air", "Arrow", "Africa", "Algebra",
        "Ball", "Bat", "Bird", "Blue", "Banana", "Butter", "Bridge",
        "Cat", "Car", "Cup", "Cake", "Cloud", "Computer", "Circle",
        "Dog", "Duck", "Door", "Doll", "Diamond", "Drum", "Dance",
        "Elephant", "Egg", "Earth", "Eel", "Eagle", "Engine", "Europe",
        "Fish", "Frog", "Fan", "Flag", "Flower", "Fire", "Forest",
        "Goat", "Grape", "Green", "Glass", "Globe", "Guitar", "Game",
        "Hat", "House", "Hand", "Heart", "Hammer", "Honey", "Horse",
        "Ice", "Ink", "Iron", "India", "Igloo", "Insect", "Island",
        "Jam", "Jug", "Jump", "Jet", "Jacket", "Japan", "Jelly",
        "Key", "King", "Kite", "Knife", "Kangaroo", "Korea", "Kilogram",
        "Lion", "Lemon", "Lamp", "Leaf", "Lock", "Library", "Ladder",
        "Moon", "Monkey", "Milk", "Mouse", "Mountain", "Mango", "Music",
        "Nail", "Nose", "Net", "Nut", "Night", "North", "News",
        "Orange", "Owl", "Ocean", "Octopus", "Oar", "Opera", "Oil",
        "Pen", "Pencil", "Paper", "Phone", "Pizza", "Pumpkin", "Piano",
        "Queen", "Question", "Quilt", "Quack", "Quick", "Quiet", "Quote",
        "Rabbit", "Rose", "Ring", "Rain", "River", "Road", "Radio",
        "Sun", "Star", "Snake", "Shoe", "Ship", "Sugar", "School",
        "Tree", "Table", "Tiger", "Train", "Truck", "Telephone", "Tennis",
        "Umbrella", "Uniform", "Unicorn", "University", "Uranus", "Ugly", "Utensil",
        "Van", "Violin", "Volleyball", "Vegetable", "Vacuum", "Vase", "Volcano",
        "Water", "Watch", "Wolf", "Wheel", "Wind", "Window", "Wig",
        "X-ray", "Xenon", "Xylophone", "Xerox", "Xanadu", "Xmas", "Xebec",
        "Yak", "Yarn", "Yellow", "Yacht", "Yogurt", "Yard", "Yesterday",
        "Zebra", "Zoo", "Zucchini", "Zipper", "Zero", "Zigzag", "Zeus"
    };

    int wordCount = sizeof(words) / sizeof(words[0]);

    // Insert words into the trie
    for (int i = 0; i < wordCount; i++) {
        insert(root, words[i]);
    }

    // Get user input for the prefix
    char prefix[100];
    printf("Enter prefix to autocomplete: ");
    scanf("%s", prefix);

    // Display autocomplete suggestions
    autocomplete(root, prefix);

    // Free allocated memory (not shown here for brevity)

    return 0;
}