#include "header.h"

void getInt(int* a) {
    int n;
    do {
        n = scanf("%d", a);
        if (n == 0) {
            printf("Incorrect input. Please, try again!");
            scanf("%*[^\n]");
        }

    } while (n == 0);
    scanf("%*c");
}

char* getstr() {
    char *ptr = (char *)malloc(1);
    char buf[81];
    int n, len = 0;
    *ptr = '\0';
    do {
        n = scanf("%80[^\n]", buf);
        if (n < 0) {
            free(ptr);
            ptr = NULL;
            continue;
        }
        if (n == 0)
            scanf("%*c");
        else {
            len += strlen(buf);
            ptr = (char *)realloc(ptr, len + 1);
            strcat(ptr, buf);
        }
    } while (n > 0);
    return ptr;
}

void getKey(Node *root) {
    char *key;
    printf("Enter the key which you want to find: ");
    key = getstr();
    Node* find = findNode(root, key);
    if (find == NULL) {
        printf("That key does not exist!\n");
        free(key);
        return;
    }
    else {
        printNode(find);
        free(key);
    }
}

Node* createNode(char* value, char* key, Node *parent) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->left = NULL;
    node->right = NULL;
    node->parent = parent;
    node->key = (char*)calloc(strlen(key) + 1, sizeof(char));
    memcpy(node->key, key, strlen(key) + 1);
    node->Info = (char*)calloc(strlen(value) + 1, sizeof(char));
    memcpy(node->Info, value, strlen(value) + 1);
    return node;
}

void getInfo(Node **root) {
    char* key;
    char* Info;
    printf("Enter the key: ");
    key = getstr();
    printf("Enter the information: ");
    Info = getstr();
    addNode(root, key, Info);
    free(key);
    free(Info);
}

int addNode(Node **root, char* key, char* Info) {
    Node *tmp = NULL;
    if (*root == NULL) {
        *root = createNode(Info, key, NULL);
        return 1;
    }
    tmp = *root;
    if (findNode(tmp, key)) {
   //     printf("The entered first key is already in the tree.\n");
        return 0;
    }
    while (tmp) {
        if (strcmp(key, tmp->key) > 0) {
            if (tmp->right) {
                tmp = tmp->right;
                continue;
            } else {
                tmp->right = createNode(Info, key, tmp);
                return 1;
            }
        } else {
            if (tmp->left) {
                tmp = tmp->left;
                continue;
            } else {
                tmp->left = createNode(Info, key, tmp);
                return 1;
            }
        }
    }
}

Node* findNode(Node *root, char* key) {
    while (root != NULL) {
        if (strcmp(key, root->key) < 0) {
            root = root->left;
            continue;
        }
        else if (strcmp(key, root->key) > 0) {
            root = root->right;
            continue;
        }
        else {
         //   printNode(root);
            return root;
        }
    }
    return NULL;
}

void printTree(Node *root, char *name, int lvl) {
    printf("\n");
    if (root) {
        printf("%d - %s\n", lvl, name);
        printf("Key: %s\n", root->key);
        printf("Info: %s\n", root->Info);
        printTree(root->left, "left", lvl + 1);
        printTree(root->right, "right", lvl + 1);
    }
}

void deleteTree(Node *root) {
    if (root) {
        deleteTree(root->left);
        deleteTree(root->right);
        free(root->Info);
        free(root->key);
        free(root);
    }
}

void deleteNode(Node *root) {
    char *key;
    printf("Enter the key: ");
    key = getstr();
    Node *check;
    check = findNode(root, key);
    if (check == NULL) {
        printf("This element is not in the tree \n");
        free(key);
        return;
    }
    removeNode(check);
    free(key);
}

void removeNode(Node *root) {
    if (root->right && root->left) {
        Node* min = getMin(root->right);
        root->key = min->key;
        root->Info = min->Info;
        removeNode(min);
        return;
    }
    else if (root->left != NULL){
        if (root->parent) {
            if (root == root->parent->left) {
                root->parent->left = root->left;
            } else {
                root->parent->right = root->left;
            }
        }
        else {
            root->left->parent = NULL;
        }
    }
    else if (root->right != NULL) {
        if (root->parent) {
            if (root == root->parent->right) {
                root->parent->right = root->right;
            } else {
                root->parent->left = root->right;
            }
        }
        else {
            root->right->parent = NULL;
        }
    }
    else {
        if (root->parent) {
            if (root == root->parent->left) {
                root->parent->left = NULL;
            } else {
                root->parent->right = NULL;
            }
        }
    }
    free(root->key);
    free(root->Info);
    free(root);
}

Node* getMin(Node *root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;

}

void nextNode(Node *root) {
    char *key;
    printf("Enter the key: ");
    key = getstr();
    Node* node = findNode(root, key);
    if (node == NULL) {
        printf("Error! That element does not exist!\n");
        free(key);
        return;
    }
    else {
        Node *find = getNext(node);
        printNode(find);
        free(key);
    }
}

Node* getNext(Node *root) {
    Node* ptr = NULL;
    if (root->right != NULL) {
        ptr = getMin(root->right);
        return ptr;
    }
    ptr = root->parent;
    while (ptr != NULL && root == ptr->right) {
        root = ptr;
        ptr = root->parent;
    }
    return ptr;
}

void printNode(Node *root) {
    if (root == NULL) {
        printf("The element does not exist!\n");
        return;
    }
    printf("Key: %s\n", root->key);
    printf("Info %s\n", root->Info);
    printf("\n");
}

char* random_string() {
    char* s;
    s = (char*)malloc(sizeof(char) * 6);
    int i, j, set_len;
    char SET[] = "abcdefghijklmn123456789";
   // srand(time(NULL));
    set_len = strlen(SET);
    for (i = 0; i < 6 - 1 && i < set_len; i++)
    {
        j = rand() % (set_len - i) + i;
        s[i] = SET[j];
        SET[j] = SET[i];
    }
    s[i] = '\0';
    return s;
}

int timing_func() {
    Node *root = NULL;
    int n = 10, cnt = 100000, i, m;
    char* k;
    char* key[100];
    clock_t first, last;
    char* info;
    info = "random_string";
    while (n-- > 0) {
        for (i = 0; i < 100; i++) {
            k = random_string();
            key[i] = (char*)calloc(6, sizeof(char));
            memcpy(key[i], k, 6);
            free(k);
        }
        for (i = 0; i < cnt; ) {
            k = random_string();
          //  printf("%d\n", cntt);
          //  printf("%s\n", k);
            if (addNode(&root, k, info))
                ++i;
            free(k);
        }
        m = 0;
        first = clock();
        for (i = 0; i < 100; i++) {
            if (findNode(root, key[i])) {
                ++m;
            }
        }
        last = clock();
        printf("test #%d, number of nodes = %d, time = %lf\n", 10 - n, (10 - n) * cnt, (double)(last - first) / CLOCKS_PER_SEC);
        for (int j = 0; j < 100; j++) {
            free(key[j]);
        }
    }
    deleteTree(root);
    return 1;
}

int load(Node** trp){
    FILE* fd = fopen("Tree.txt", "r+b");
    char* key;
    char* info;
    int key_len, info_len;
    fseek(fd, 0, SEEK_END);
    long end = ftell(fd);
    fseek(fd, 0, SEEK_SET);
    while(ftell(fd) != end) {
        fread(&key_len, sizeof(int), 1, fd);
        key = (char *) calloc(1, key_len);
        fread(key, sizeof(char), key_len, fd);
        fread(&info_len, sizeof(int), 1, fd);
        info = (char *) calloc(1, info_len);
        fread(info, sizeof(char), info_len, fd);
        addNode(trp, key, info);
        free(key);
        free(info);
    }
    fclose(fd);
    return 0;
}

void save_tree(Node* ptr, FILE* fd){
    if (ptr) {
        unsigned int key_len = strlen(ptr->key) + 1;
        unsigned int info_len = strlen(ptr->Info) + 1;
        fwrite(&key_len, sizeof(int), 1, fd);
        fwrite(ptr->key, 1,  key_len, fd);
        fwrite(&info_len, sizeof(int), 1, fd);
        fwrite(ptr->Info, 1, info_len, fd);
        save_tree(ptr->left, fd);
        save_tree(ptr->right, fd);
    }
}


int save(Node** root){
    FILE* fd = fopen("Tree.txt", "w+b");
    Node* ptr = *root;
    save_tree(ptr, fd);
    fclose(fd);
    return 0;
}