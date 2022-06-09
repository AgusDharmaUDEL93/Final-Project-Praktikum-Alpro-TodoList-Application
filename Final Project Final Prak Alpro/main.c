#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct list{
    char todo[200];
    char deadline[200];
    struct list *next;
} *dataTodo, *head, *tail;

int jumlah = 0;

void menampilkanTodoList ();
void menambahTodolist(char varTodoList[], char deadline[]);
bool menghapusTodoList (int nomorData);
void tampilanMenambah ();
void tampilanMenghapus ();
void tampilanUtama ();
void tampilanMengedit();
bool mengeditTodoList(int angka, char string[200], char string1[200]);

int main() {
    tampilanUtama();
    return 0;
}

void menampilkanTodoList() {
    printf("_______________________________________\n");
    printf("TODO LIST ANDA :\n");
    int num = 0;
    char *check;
    dataTodo = head;
    FILE *f = fopen("data.txt", "w");
    while(dataTodo != NULL){
        num ++;
        printf("List ke-%i\n", num);
        printf("List : %s", dataTodo->todo);
        check = strstr(dataTodo->todo, "\n");
        if (check != NULL){
            fputs(dataTodo->todo,f);
        } else{
            printf("\n");
            fputs(strcat(dataTodo->todo, "\n"),f);
        }
        printf("Deadline : %s", dataTodo->deadline);
        check = strstr(dataTodo->deadline, "\n");
        if (check != NULL){
            fputs(dataTodo->deadline,f);
        } else{
            fputs(strcat(dataTodo->deadline, "\n"),f);
        }
        printf("\n");
        dataTodo = dataTodo->next;
    }
    fclose(f);

}

void menambahTodolist(char *varTodoList, char *deadline) {
    dataTodo = (struct list*) malloc(sizeof (struct list));

    strcpy(dataTodo->todo, varTodoList);
    strcpy(dataTodo->deadline, deadline);

    if(head == NULL){
        head = tail = dataTodo;
    } else {
        tail->next = dataTodo;
        tail = dataTodo;
    }
    jumlah++;
    tail->next = NULL;
}

bool menghapusTodoList(int nomorData) {
    struct list *temp = head;
    struct list *previous = head;
    if(nomorData>jumlah){
        return false;
    } else{
        if(head==NULL){
            return false;
        }else if(nomorData == 1){
            head = head ->next;
            free(temp);

            return true;
        }else if (nomorData == jumlah){
            while(temp->next!=tail){
                temp=temp->next;
            }
            free(tail);
            tail=temp;
            tail->next=NULL;
            return true;
        } else{
            for (int i = 0; i < nomorData-1; i++) {
                temp = temp->next;
            }
            for (int i = 0; i < nomorData-2; i++) {
                previous = previous->next;
            }
            previous->next = previous ->next->next;
            free(temp);
            return true;
        }
    }
}

void tampilanMenambah() {
    printf("_______________________________________\n");
    printf("TAMBAH LIST\n");
    printf("Input y untuk lanjut atau x jika batal) :");
    char tambahanTodo[200];
    char deadlineTodo[200];
    char status;
    scanf("%c", &status);
    fflush(stdin);
    if (status == 'x' || status == 'X'){
        return;
    }else if (status == 'y' || status == 'Y') {
        printf("Masukkan List :");
        gets(tambahanTodo);
        printf("Masukkan Deadline :");
        gets(deadlineTodo);
        menambahTodolist(tambahanTodo, deadlineTodo);
    } else{
        printf("Masukkan Input Yang Benar !\n");
    }
}

void tampilanMenghapus() {
    printf("_______________________________________\n");
    printf("HAPUS LIST\n");
    int angka;
    printf("Input y untuk lanjut atau x jika batal) :");
    char status;
    scanf("%c", &status);
    fflush(stdin);
    if(status == 'x' || status == 'X'){
        return;
    } else if (status == 'y' || status == 'Y'){
        printf("Masukkan nomor list yang ingin dihapus :");
        scanf("%i", &angka);
        bool sukses = menghapusTodoList(angka);
        if(sukses == false){
            printf("Maaf permintaan anda gagal\n");
        } else{
            jumlah--;
            printf("Sukses menghapus\n");
        }
    } else{
        printf("Masukkan Input Yang Benar !\n");
    }
}

void tampilanUtama() {
    FILE *f = fopen("data.txt", "r");
    if(f){
        char txt[200];
        short c=-1,m=1;

        while(fgets(txt,200,f)!=NULL){
            ++c;
            if(c==0){
                dataTodo = (struct list*) malloc(sizeof (struct list));
                strcpy(dataTodo->todo, txt);
                ++m;
            }else if(c==1){
                strcpy(dataTodo->deadline, txt);
                if(head == NULL){
                    head = tail = dataTodo;
                } else {
                    tail->next = dataTodo;
                    tail = dataTodo;
                }
                jumlah++;
                tail->next = NULL;
                c=-1;
            }
        }
        printf("---------------\n");
        fclose(f);
    } else{
        printf("Tidak ada file\n");
    }
    printf("APLIKASI TO DO LIST\nALGORITMA DAN PEMROGRAMAN\n");
    while (true){
        fflush(stdin);
        menampilkanTodoList();
        printf("MENU\n1.\tTambah List\n2.\tHapus List\n3. \tEdit List\nx.\tKeluar\n");
        printf("Pilihan Anda :");
        char menu;
        scanf("%c", &menu);
        getchar();
        switch (menu){
            case  '1' :
                tampilanMenambah();
                break;
            case '2' :
                tampilanMenghapus();
                break;
            case '3':
                tampilanMengedit();
                break;
            case 'x' :
                return;
            default:
                printf("Mohon Pilih Sesuai Menu !!\n");
                break;
        }
    }
}

void tampilanMengedit() {
    printf("_______________________________________\n");
    printf("EDIT LIST\n");
    printf("Input y untuk lanjut atau x jika batal) :");
    char status;
    int angka;
    char newTodo[200];
    char newDeadlineTodo[200];
    scanf("%c", &status);
    fflush(stdin);
    if (status == 'x' || status == 'X'){
        return;
    }else if (status == 'y' || status == 'Y') {
        printf("Masukkan nomor list yang ingin diedit :");
        scanf("%i", &angka);
        printf("Masukkan List Terbaru :");
        fflush(stdin);
        gets(newTodo);
        printf("Masukkan Deadline Terbaru :");
        gets(newDeadlineTodo);
        fflush(stdin);
        bool sukses = mengeditTodoList(angka, newTodo, newDeadlineTodo);
        if(sukses == false){
            printf("Maaf permintaan anda gagal\n");
        } else{
            jumlah--;
            printf("Sukses mengedit\n");
        }
    } else{
        printf("Masukkan Input Yang Benar !\n");
    }
}

bool mengeditTodoList(int angka, char newTodo[200], char newDeadlineTodo[200]) {
    struct list *temp = head;
    if(angka>jumlah){
        return false;
    } else{
        if(head==NULL){
            return false;
        }else{
            for (int i = 0; i < angka-1; i++) {
                temp = temp->next;
            }
            strcpy(temp->todo, newTodo);
            strcpy(temp->deadline, newDeadlineTodo);
            return true;
        }
    }
}
