#include <iostream>
#include <windows.h>
#include <winSock.h>
#include <stdlib.h>
#include <string>
#include <mysql.h>

#include <typeinfo>

using namespace std;

MYSQL mysql;
MYSQL_FIELD *fd;
char field[255][255];
MYSQL_RES *res;
MYSQL_ROW column;
char query[150];

bool ConnectDatabase();
void FreeConnect();
bool QueryDatabase();

int main()
{
    ConnectDatabase();
    QueryDatabase();
    FreeConnect();
    return 0;
}

bool ConnectDatabase()
{
    mysql_init(&mysql);
    const char host[] = "39.100.71.192";
    const char user[] = "peter";
    const char psw[] = "none";
    const char db[] = "peter";
    const int port = 3306;
    if(!(mysql_real_connect(&mysql, host, user, psw, db, port, NULL, 0)))
    {
        cout<< "error connect" << mysql_error(&mysql) <<endl;
        return false;
    }
    else
    {
        cout<< "connect successful" <<endl;
        return true;
    }
}

bool QueryDatabase()
{
    strcpy(query, "select * from user");
    mysql_query(&mysql, "set names gbk");
    if(mysql_query(&mysql, query))
    {
        cout<< "query failed" << mysql_error(&mysql) <<endl;
        return false;
    }
    else
    {
        cout<< "query successful" <<endl;
    }

    if(!(res = mysql_store_result(&mysql)))
    {
        cout<< "get res error: " << mysql_error(&mysql) <<endl;
        return false;
    }

    //get rows;
    int num_rows = mysql_affected_rows(&mysql);
    cout<< "num of column return: " << num_rows <<endl;
    //get columns
    int num_cloumns = mysql_num_fields(res);
    cout<< "num of rows return: " << num_cloumns <<endl;

    // mysql field
    char *str_field[255];
    for(int i=0; i<6; i++)
    {
        str_field[i] = mysql_fetch_field(res) -> name;
    }
    for(int i=0; i<6; i++)
    {
        cout<< str_field[i] << " | ";
    }
    cout<<endl;
    while(column = mysql_fetch_row(res))
    {
        cout<< sizeof(column[3]);
        if((string)column[2] == "0")
        {
            strcpy(column[2], "unkown");
        }
        else if((string)column[2] == "1")
        {
            strcpy(column[2], "female");
        }
        else if((string)column[2] == "2")
        {
            strcpy(column[2], "male");
        }
        else
        {
            strcpy(column[2], "error");
        }
        for(int i=0; i<num_cloumns; i++)
        {
            cout<< column[i] << " | ";
        }
        cout<<endl;
    }
    return true;
}

void FreeConnect()
{
    mysql_free_result(res);
    mysql_close(&mysql);
}
