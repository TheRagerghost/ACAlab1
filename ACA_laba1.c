#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>


unsigned int _move, _compare;

struct pairVID {
    double f;
    unsigned int id;
} *_arrinit = NULL;


FILE* GetFile (FILE* file) {
    char fname [69];
    while (file == NULL) {
        printf("Enter name of da file or file path (Example: file.dat or /Users/username/Desktop/file.csv):");
        scanf("%s", fname);
        file=fopen(fname, "rb");
    }
    return file;
}


struct pairVID* Manual (int size) {
    int i;
    struct pairVID* _elems;
    _elems = (struct pairVID*) malloc (sizeof(struct pairVID)*size);
    for (i = 0; i < size; i++) {
        printf("\nEnter value of element %d:", i);
        scanf("%lf", &_elems[i].f);
        printf("\nEnter id of element %d:", i);
        scanf("%u", &_elems[i].id);
    }
    return _elems;
}

struct pairVID* DupeArray (struct pairVID* _arr1, int size ) {
    struct pairVID* _arr2;
    _arr2 = (struct pairVID*) malloc (sizeof(struct pairVID)* size);
    int i = 0;
    for (i = 0; i < size; i++)
        _arr2 [i] = _arr1 [i];
    return _arr2;
}

void Swap (struct pairVID *a, struct pairVID *b) {
    struct pairVID c;
    c = *a;
    *a = *b;
    *b = c;
}

void Sort_bubble (struct pairVID* _arbub, int size) {
    int i;
    char flag;
    do {
        flag = 0;
        for (i = 1; i < size; i++) {
            if (_arbub[i].id < _arbub[i-1].id) {
                Swap(&_arbub[i], &_arbub[i-1]);
                flag = 1;
                _move++;
            }
            _compare++;
        }
    } while (flag);
}

void Sort_quick (struct pairVID* _arq, int first, int last) {
    int i = first, j = last, x = _arq[(first + last) / 2].id;
    do {
        while (_arq[i].id < x) {
            i++;
            _compare++;
        }
        while (_arq[j].id > x) {
            j--;
            _compare++;
        }
        
        if(i <= j) {
            if (_arq[i].id > _arq[j].id) {
                Swap(&_arq[i], &_arq[j]);
                _compare++;
                _move++;
            }
            i++;
            j--;
        }
    } while (i <= j);
    
    if (i < last)
        Sort_quick(_arq, i, last);
    if (first < j)
        Sort_quick(_arq, first, j);
}

void Sort_insertion (struct pairVID* _ari, int size) {
    struct pairVID _newElem;
    int location,i;
    
    for ( i = 1; i < size; i++) {
        _newElem = _ari[i];
        location = i - 1;
        while(location >= 0 && _ari[location].id > _newElem.id) {
            _compare++;
            _ari[location+1] = _ari[location];
            _move++;
            location = location - 1;
        }
        _ari[location+1] = _newElem;
        _compare++;
        _move++;
    }
}

typedef struct _node {
    struct pairVID key;
    struct _node *left, *right;
} node;

node* AddNewNode(struct pairVID val) {
    node* nnode = (node*) malloc (sizeof(node));
    nnode->key = val;
    nnode->left = NULL;
    nnode->right = NULL;
    return nnode;
}

node* AddTree(node *root, struct pairVID _art) {
    _compare++;
    if (root == NULL) {
       
        root = AddNewNode(_art);
        _move++;
        
    } else if (_art.id < root->key.id ) {
       
        if (NULL == root->left)
            root->left = AddNewNode(_art);
        else
            AddTree(root->left, _art);
        
    } else if (_art.id > root->key.id) {
        
        if (NULL == root->right)
            root->right = AddNewNode(_art);
        else
            AddTree(root->right, _art);
    }
    return root;
}

unsigned int Search_tree(node *root, unsigned int search) {
    _compare++;
    if (root != NULL){
        printf("%d hasn't been found.\n", search);
        return 0;
    } else if (search == root->key.id) {
        printf("%d has been found.\n", root->key.id);
        return root->key.id;
    } else if (search < root->key.id)
        return Search_tree(root->left, search);
    else if (search > root->key.id)
        return Search_tree(root->right, search);
    else
        return 0;
}

node* Sort_binary (struct pairVID* _arbin, int size) {
    int i = 0;
    node *mnode = NULL;
    while (i < size) {
        mnode = AddTree(mnode, _arbin[i]);
        _move++;
        i++;
    }
    return mnode;
}


void ArrPrint (struct pairVID* _arr, int size) {
    int j;
    printf("\tAscending:\t\t|\t\tDescending: \n");
    for(j = 0; j < size; j++) {
        printf("%lf\t%u\t|\t%lf\t%u\n",(_arr[j].f), (_arr[j].id), (_arr[size-j-1].f), (_arr[size-j-1].id));
    }
}

unsigned int Search_linear (struct pairVID* _arr, int size, unsigned int search) {
    int i;
    for (i = 0; i < size; i++) {
        if (_arr[i].id == search) {
            printf("%d has position %d.\n", _arr[i].id , i);
            break;
        }
        _compare++;
    }
    if (i == size)
        printf("There's no %d in da array.\n", search);
    
    return i;
}

int Search_interpolation (unsigned int search, struct pairVID* _arr, int low, int high) {
    int mid = -1;
    int comparisons = 1;
    int index = -1;
    
    while((_arr[high].id != _arr[low].id) && (search >= _arr[low].id) && (search <= _arr[high].id)) {
        comparisons++;
        mid = low + ((search - _arr[low].id) * (high - low) / (_arr[high].id - _arr[low].id));
        if(_arr[mid].id == search) {
            index = mid;
            break;
        } else {
            if(_arr[mid].id < search) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
    }
    if (index > 0)
        printf("\n%d has position %d", search,index);
    else
        printf("\n%d hasn't been found.", search);
    printf("\nTotal compares count: %d\n", --comparisons);
    return index;
}

int Search_binary(int search, struct pairVID* _arr, int n) {
    char _isFound = 0;
    int low, high, mid;
    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (search < _arr[mid].id) {
            _compare++;
            high = mid - 1;
        } else if (search > _arr[mid].id) {
            low = mid + 1;
            _compare++;
        } else {
            printf("%d has position %d.\n", _arr[mid].id , mid);
            _isFound = 1;
            return mid;
        }
        _move++;
    }
    
    if (_isFound == 0)
        printf("%d hasn't been found.\n", search);
    
    return -1;
}

void ClearMC (){
    _move = 0;
    _compare = 0;
}

int main (void) {
    int i = 0, size;
    unsigned int search = 0;
    FILE *file;
    char ch;
    
    printf("\nChoose method:\nType 'r' to read from file\nType 'e' to enter from the keyboard\n");
    scanf("%c%*c", &ch);
    switch (ch) {
        case 'r':
            file = fopen("file.csv", "rb");
            if (file == NULL)  file = GetFile(file);
            
            _arrinit=(struct pairVID*) malloc (sizeof(struct pairVID));
            while (fscanf (file, "%lf%*c%u", &(_arrinit[i].f), &(_arrinit[i].id))!=EOF) {
                i++;
                _arrinit=(struct pairVID*) realloc (_arrinit,(i+1)*sizeof(struct pairVID));
            }
            i--;
            size = i;
            fclose(file);
            break;
            
        case 'e':
            printf("\nNumber of values:");
            scanf("%d", &size);
            _arrinit = Manual(size);
            break;
            
        case 'a':
            printf("\n\n\n                              .                : :\n            _..----..__   __..:'.-'''-.-''    .  :\n          .'      ,    '''    '    :   .'    /  '\n         ',                  ( -=o):(o=-)   .  :\n        :     ,               ''.  ;  .'  __:  :\n        :          :      ,      '.0.''.-'.))  :  __..--\n        :           :                ._.-'__| ':''.\n         .           :   ,   ..  :.-' __.' /   ;    . \n        .'       ,   :    _.'  '. '.''    /   /  '\n      .:. .'.        :--:'_..--'''.))  .  ' -'    __.--'\n    .''::'   '-.  .-''.  '.   .             __.--'\n    :...:     __|  '.  '..))     '    __.--'\n    ::'':.--''   '.)))          __.--'\n_..--:.::'   .         .  __.--'\n      :' .:.        __.--'\n  '    .::' : __.--'\nAndrej__' .::'\n..--''   ':::'\n\n\n");
            exit(-1);
            break;
            
        default:
            printf( "\nLol, let's all choose non existing variants. Bye ^_^\n" );
            exit(-1);
    }
    
    struct pairVID* _temparr = NULL;
    clock_t starttime;
    clock_t finishtime;
    
    ClearMC ();
    printf("\n\tSort type: Bubble\n");
    _temparr = DupeArray(_arrinit, size);
    starttime = clock();
    Sort_bubble(_temparr, size);
    finishtime = clock();
    double _duration = (double)(finishtime - starttime) / CLOCKS_PER_SEC;
    printf("Sort duration: %lf s\n", _duration);
    printf("Compares count = %u\nMoves count = %u\n", _compare, _move);
    
    ClearMC ();
    printf("\n\tSort type: Quick\n");
    _temparr = DupeArray(_arrinit, size);
    starttime = clock();
    Sort_quick(_temparr, 0, size-1);
    finishtime = clock();
    _duration = (double)(finishtime - starttime) / CLOCKS_PER_SEC;
    printf("Sort duration: %lf s\n", _duration);
    printf("Compares count = %u\nMoves count = %u\n", _compare, _move);
    
    ClearMC ();
    printf("\n\tSort type: Insertion\n");
    _temparr = DupeArray(_arrinit, size);
    starttime = clock();
    Sort_insertion (_temparr, size);
    finishtime = clock();
    _duration = (double)(finishtime - starttime) / CLOCKS_PER_SEC;
    printf("Sort duration: %lf s\n", _duration);
    printf("Compares count = %u\nMoves count = %u\n", _compare, _move);
    
    ClearMC ();
    printf("\n\tSort type: Binary\n");
    node* mnode;
    _temparr = DupeArray(_arrinit, size);
    starttime = clock();
    mnode = Sort_binary(_temparr, size);
    finishtime = clock();
    _duration = (double)(finishtime - starttime) / CLOCKS_PER_SEC;
    printf("Sort duration: %lf s\n", _duration);
    printf("Compares count = %u\nMoves count = %u\n", _compare, _move);
    
    printf("\nChoose search value getting method:\nType 'r' to use random\nType 'e' to enter from da keyboard\n");
    scanf(" %c", &ch);
    switch (ch) {
        case 'r':
            srand((unsigned) time(NULL));
            i = rand()%size;
            search = _arrinit[i].id;
            break;
            
        case 'e':
            printf("\nSearch value:");
            scanf("%d", &search);
            break;
            
        default:
            printf( "\nLol, let's all choose non existing variants. Bye ^_^\n" );
            exit(-1);
    }
    
    
    printf("\n\tSearch type: Linear\n");
    Sort_quick(_arrinit, 0, size-1);
    ClearMC ();
    starttime = clock();
    Search_linear(_arrinit, size, search);
    finishtime = clock();
    _duration = (double)(finishtime - starttime) / CLOCKS_PER_SEC;
    printf("Search duration: %lf s\n", _duration);
    printf("Compares count = %u\n ", _compare);
    
    
    ClearMC ();
    printf("\n\tSearch type: Tree\n");
    _temparr = DupeArray(_arrinit, size);
    starttime = clock();
    Search_tree(mnode, search);
    finishtime = clock();
    _duration = (double)(finishtime - starttime) / CLOCKS_PER_SEC;
    printf("Search duration: %lf s\n", _duration);
    printf("Compares count = %u\n", _compare);
    
    ClearMC ();
    printf("\n\tSearch type: Interpolation");
    starttime = clock();
    Search_interpolation(search, _arrinit, 0, size-1);
    finishtime = clock();
    _duration = (double)(finishtime - starttime) / CLOCKS_PER_SEC;
    printf("Search duration: %lf s\n", _duration);
    
    ClearMC ();
    printf("\n\tSearch type: Binary\n");
    _temparr = DupeArray(_arrinit, size);
    starttime = clock();
    Search_binary(search, _arrinit, size);
    finishtime = clock();
    _duration = (double)(finishtime - starttime) / CLOCKS_PER_SEC;
    printf("Search duration: %lf s\n", _duration);
    printf("Compares count = %u\n ", _compare);
    
    printf("\nDo ya want initial array to be printed?\nType 'y' (aka YEAH) or 'n' (aka NOPE)\n");
    scanf(" %c", &ch);
    if (ch == 'y')
        ArrPrint(_arrinit, size);
    
    free(_arrinit);
    return 0;
}

