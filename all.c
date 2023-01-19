#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct Post_info Pinfo;
typedef struct User_info Uinfo;
struct Post_info//post structre
{
    int postID;
    int like;
    char *post;
    Pinfo *next;
};


struct User_info//user and main structre
{
    char *username;
    char *password;
    struct Post_info *head1;
    Uinfo *next1;
};




void tuti_ut(Uinfo *head, int *numofnods, int *numofpost);
int logout(int loginflag);
void signup(Uinfo *head);
Uinfo *creat_node(char *name, char *pass);
void write_file(Uinfo *head);
void createList(Uinfo *head, Uinfo *node);
void like(Uinfo *head, int numofpost);
void login(int nomofnodes, Uinfo *head, char **loginname);
void checknull(char *check, int n);
void find_user(int numofnodes, Uinfo *head);
void post(char *loginname, Uinfo *head, int numofnodes, int pid);
Pinfo *creat_node_post(int *pID, char *pst);
void info(int numofnodes, Uinfo *head);
void delete(Uinfo *headdelete, char *username);
void createList_post(Pinfo *head1, Pinfo *node, Uinfo *head);



void tuti_ut(Uinfo *head, int *numofnodes, int *numofpost)
{
    int loginflag = 0;
    char *loginname = NULL;
    int pid = 0;
    int logoutflag = 5;
    while (1)
    {
        int result1 = 1, result2 = 1, result3 = 1, result4 = 1, result5 = 1, result6 = 1, result7 = 1, result8 = 1, i = 0;
        char *inter = (char *)malloc(1 * sizeof(char));//geting order from user and puting it in dynamic array
        printf("Enter your order:");
        inter[i] = getchar();
        while (inter[i] != ' ')//allucating memory for order
        {
            i++;
            inter = (char *)realloc(inter, (i + 1) * sizeof(char));
            checknull(inter, i + 1);
            inter[i] = getchar();
        }
        inter[i] = '\0';

        result2 = strcmp(inter, "login");//checking order with strcmp
        if (result2 == 0)
        {
            login(*numofnodes, head, &loginname);
            free(inter);
            fflush(stdin);
            loginflag = 1;//login flag for resist program
            logoutflag = 5;
        }
        result1 = strcmp(inter, "signup");
        if (result1 == 0)
        {
            if (loginflag == 1)
            {
                printf("you have to logout first\n");
            }
            else
            {
                signup(head);
                (*numofnodes)++;//for counting how many account created
                free(inter);
                fflush(stdin);
            }
        }
        result3 = strcmp(inter, "info");
        if (result3 == 0)
        {
            if (loginflag == 1)
            {
                info(*numofnodes, head);
            }
            else
            {
                printf("you have to login first\n");
            }
            free(inter);
            fflush(stdin);
        }
        result4 = strcmp(inter, "find_user");
        if (result4 == 0)
        {
            find_user(*numofnodes, head);
            free(inter);
            fflush(stdin);
        }
        result5 = strcmp(inter, "logout");
        if (result5 == 0)
        {
            logoutflag = logout(loginflag);
            free(inter);
            fflush(stdin);
        }
        result6 = strcmp(inter, "post");

        if (result6 == 0)
        {
            if (loginflag == 1 && logoutflag != 0)
            {
                pid++;
                (*numofpost)++;//for counting how many post uploaded
                post(loginname, head, *numofnodes, pid);
            }
            else
            {
                printf("you have to login first\n");
            }
            free(inter);
            fflush(stdin);
        }
        result7 = strcmp(inter, "delete");
        if (result7 == 0)
        {
            if (loginflag == 1 && logoutflag != 0)
            {
                delete (head, loginname);
                free(inter);
                fflush(stdin);
            }
            else
            {
                printf("you have to login first\n");
            }
        }
        result8 = strcmp(inter, "like");
        if (result8 == 0)
        {
            like(head, *numofpost);
            free(inter);
            fflush(stdin);
        }
        write_file(head);
    }
}

void signup(Uinfo *head)
{
    int i = 0;
    int j = 0;

    char *name = (char *)malloc(1 * sizeof(char));//geting username from stdin and puting it in dynamic array
    name[i] = getchar();
    while (name[i] != ' ')
    {
        i++;
        name = (char *)realloc(name, (i + 1) * sizeof(char));
        checknull(name, i + 1);
        name[i] = getchar();
    }
    name[i] = '\0';
    char *pass = (char *)malloc(1 * sizeof(char));//geting password from stdin and puting it in dynamic array
    pass[j] = getchar();
    while (pass[j] != '\n')
    {
        j++;
        pass = (char *)realloc(pass, (i + 1) * sizeof(char));
        checknull(pass, i + 1);
        pass[j] = getchar();
    }
    pass[j] = '\0';
    Uinfo *new_node = creat_node(name, pass);//creating node with our function
    Uinfo *temp = head;
    while (temp->next1 != NULL)
    {
        temp = temp->next1;
    }
    createList(temp, new_node);//create linkedlist with function
}

void login(int numofnodes, Uinfo *head, char **loginname)
{
    int i = 0;
    int j = 0;
    int k = 0;
    char *name = (char *)malloc(1 * sizeof(char));//geting username from stdin and puting it in dynamic array
    name[i] = getchar();
    while (name[i] != ' ')
    {
        i++;
        name = (char *)realloc(name, (i + 1) * sizeof(char));
        checknull(name, i + 1);
        name[i] = getchar();
    }
    name[i] = '\0';
    char *pass = (char *)malloc(1 * sizeof(char));//geting password from stdin and puting it in dynamic array
    pass[j] = getchar();
    while (pass[j] != '\n')
    {
        j++;
        pass = (char *)realloc(pass, (i + 1) * sizeof(char));
        checknull(pass, i + 1);
        pass[j] = getchar();
    }
    pass[j] = '\0';
    Uinfo *temp = head;
    while (numofnodes > k)
    {
        if ((strcmp(temp->next1->password, pass) == 0) && (strcmp(temp->next1->username, name) == 0))//matching user and pass for login account
        {
            printf("you are succsfully loggedin\n");
            *loginname = temp->next1->username;//this later use for resistanting or checking name of account that loggedin
            return;
        }
        else
        {
            printf("your username and password is incorect\n");
            return;
        }
        temp = temp->next1;
        k++;
    }
}

int logout(int loginflag)
{

    if (loginflag == 1)
    {
        printf("you are loggedout\n");
        return 0;
    }
    else
    {
        printf("you are not login\n");
    }
}

void post(char *loginname, Uinfo *head, int numofnodes, int pid)
{
    int i = 0;
    int k = 0;
    char *post = (char *)malloc(1 * sizeof(char));//geting post note from stdin and puting it in dynamic array
    post[i] = getchar();
    while (post[i] != '\n')
    {
        i++;
        post = (char *)realloc(post, (i + 1) * sizeof(char));
        checknull(post, i + 1);
        post[i] = getchar();
    }
    post[i] = '\0';
    Uinfo *temp = head;

    while (numofnodes > k)
    {
        if (temp->next1 == NULL)
        {
            printf("you have to login first");
            return;
        }
        if (strcmp(temp->next1->username, loginname) == 0)
        {
            break;
        }
        temp = temp->next1;
        k++;
    }
    Pinfo *temppost = (Pinfo *)malloc(sizeof(Pinfo));
    temppost = temp->head1;
    Pinfo *newnode = (Pinfo *)malloc(sizeof(Pinfo));
    if (newnode == NULL)
    {
        while (!newnode)
        {
            newnode = (Pinfo *)malloc(sizeof(Pinfo));
        }
    }

    newnode = creat_node_post(pid, post);//creating node for post txt and post id
    createList_post(temppost, newnode, head);//creating linked list with function
    printf("post sucssfully uploaded\n");
    while (temppost->next != NULL)
    {
        temppost = temppost->next;
    }

    while (temppost != NULL)
    {
        printf("%d:", temppost->postID);
        printf("%s\n", temppost->post);
        temppost = temppost->next;
    }
}

void find_user(int numofnodes, Uinfo *head)
{
    int i = 0;
    int k = 0;
    char *name = (char *)malloc(1 * sizeof(char));//geting username from stdin and puting it in dynamic array
    name[i] = getchar();
    while (name[i] != '\n')
    {
        i++;
        name = (char *)realloc(name, (i + 1) * sizeof(char));
        checknull(name, i + 1);
        name[i] = getchar();
    }
    name[i] = '\0';
    Uinfo *temp = head;
    Pinfo *temppost = head->head1->next;

    while (numofnodes > k)
    {
        if ((strcmp(temp->next1->username, name) == 0))//checking to make sure that this username is available
        {
            printf("%s \n", temp->next1->username);
            while (temppost != NULL)
            {
                printf("%d:", temppost->postID);
                printf("%s\t", temppost->post);
                printf("like:%d\n", temppost->like);
                temppost = temppost->next;
            }
            return;
        }

        temp = temp->next1;
        k++;
    }
    printf("This username is not availble\n");
    return;
}

void info(int numofnodes, Uinfo *head)
{
    int i = 0;
    int k = 0;
    char *name = (char *)malloc(1 * sizeof(char));
    name[i] = getchar();
    while (name[i] != '\n')
    {
        i++;
        name = (char *)realloc(name, (i + 1) * sizeof(char));
        checknull(name, i + 1);
        name[i] = getchar();
    }
    name[i] = '\0';
    Uinfo *temp = head;
    Pinfo *temppost = head->head1->next;

    while (numofnodes > k)
    {

        printf("%s\n", temp->next1->username);
        printf("%s\n", temp->next1->password);
        while (temppost != NULL)
        {
            printf("%d:", temppost->postID);
            printf("%s\t", temppost->post);
            printf("like:%d\n", temppost->like);
            temppost = temppost->next;
        }
        return;

        temp = temp->next1;
        k++;
    }
    return;
}

void delete(Uinfo *head, char *username)
{
    int post_id = 0;
    scanf("%d", &post_id);
    Uinfo *temp = head;
    while (strcmp(temp->next1->username, username) != 0)
    {
        temp = temp->next1;
    }
    Pinfo *tempdelete = temp->head1;
    while (1)
    {
        if (tempdelete->next->postID == post_id)
        {
            printf("post deleted\n");
            tempdelete->next = tempdelete->next->next;//linking previuse node to the next node
            break;
        }
        tempdelete = tempdelete->next;
    }
}

void like(Uinfo *head, int numofpost)
{
    int k = 0;
    const char *postID = getchar();
    int pid = (int)(postID);//casting char to int
    pid = pid - 48;
    Pinfo *temppost = (Pinfo *)malloc(sizeof(Pinfo));
    Uinfo *temp = head;
    temppost = temp->head1;
    Pinfo *newnode = (Pinfo *)malloc(sizeof(Pinfo));
    if (newnode == NULL)
    {
        while (!newnode)
        {
            newnode = (Pinfo *)malloc(sizeof(Pinfo));
        }
    }
    while (numofpost > k)
    {
        if (pid == temppost->next->postID)
        {
            temppost->next->like = temppost->next->like + 1;
            printf("post sucssfuly liked\n");
            return;
        }
        temppost = temppost->next;
        k++;
    }
    printf("this postID not availble\n");
    return;
}

Uinfo *creat_node(char *name, char *pass)//creating node for user structure
{
    Uinfo *newnode = (Uinfo *)malloc(sizeof(Uinfo));
    if (newnode == NULL)
    {
        while (!newnode)
        {
            newnode = (Uinfo *)malloc(sizeof(Uinfo));
        }
    }

    newnode->username = name;
    newnode->password = pass;
    newnode->head1 = (Pinfo *)malloc(sizeof(Pinfo));
    newnode->head1->next = NULL;
    newnode->next1 = NULL;
    return newnode;
}

Pinfo *creat_node_post(int *pID, char *pst)//creating node for post structure
{
    Pinfo *newnode = (Pinfo *)malloc(sizeof(Pinfo));
    if (newnode == NULL)
    {
        while (!newnode)
        {
            newnode = (Pinfo *)malloc(sizeof(Pinfo));
        }
    }
    newnode->post = pst;
    newnode->postID = pID;
    newnode->next = NULL;
    return newnode;
}

void createList(Uinfo *head, Uinfo *node)//linked list for user structure
{
    Uinfo *temp = head;
    while (temp->next1 != NULL)
    {
        temp = temp->next1;
    }
    temp->next1 = node;

    printf("your account succesfully added\n");
}

void createList_post(Pinfo *head1, Pinfo *node, Uinfo *head)//linked list for post structure
{
    Uinfo *temp = head->head1;
    while (temp->next1 != NULL)
    {
        temp = temp->next1;
    }
    temp->next1 = node;
}

void checknull(char *check, int n)//checking that malloc dosent return null
{
    if (check == NULL)
    {
        while (!check)
        {
            check = (char *)realloc(check, n * sizeof(char));
        }
    }
}

void write_file(Uinfo *head)
{
    FILE *fp = fopen("accounts.txt", "w");
    FILE *f2p = fopen("post.txt", "w");
    Uinfo *temp = head->next1;
    while (temp != NULL)
    {
        Pinfo *cur = temp->head1;
        fprintf(fp, "%s", temp->username);
        fprintf(fp, "%s", temp->password);
        while (cur != NULL)
        {
            fprintf(f2p, "%s", cur->post);
            fprintf(f2p, "%s", cur->postID);
            fprintf(f2p, "%d\n", cur->like);
            cur = cur->next;
        }
        temp = temp->next1;
    }
    fclose(fp);
    fclose(f2p);
}

int main()
{
    int numofnodes = 0;
    int numofpost = 0;
    Uinfo *head = creat_node('m', 'm');
    tuti_ut(head, &numofnodes, &numofpost);
}
