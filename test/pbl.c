#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int import_data(char);
int update_data(char, char);

int main(void) {
    //char *openhtml = "open loginscene.html";
    //system(openhtml);
    char url[256] = "https://pro-c.ics.es.osaka-u.ac.jp/wiki.cgi?page=Programming+C/" ;
    char id[16] = "192.168.2.101";

    update_data(id,url);
    import_data(id);
    return 0;
}

/* ファイルの形式
 * 各行に
 * (URL)(空白)(回数)
 * となるファイル (IPアドレス).
 */


/* クライアントのIPアドレス，URLへの接続回数を保存するデータファイルを読み込む．
 * 存在しない場合は作成．
 * 成功時には0を返す．
 * 失敗時には―1を返す．
 * 引数はIPアドレスのchar型配列
 */
int inport_data(char clip){
    FILE    *fp;
    char    filename[19];

    sprintf(filename,"%s.db",clip);

    fp = fopen(filename,"w+");
    /*最初のアクセス時に問答無用でこちらからhtmlを送り付ける*/
    fclose(fp);
}

/* クライアントのIPアドレス，URLへの接続回数をファイルに保存する．
 * 成功時には0を返す．
 * 失敗時には-1を返す．
 * 引数はIPアドレス,URLの各char型配列,
 */
int update_data(char clip, char clurl){
    FILE    *inp,*out;
    int     count;
    char    url[1000];
    char    filename[19];

    sprintf(filename,"%s.db",clip);
    inp = fopen(filename,"r+");
    out = fopen("temp.txt","w");

    while(fscanf(inp,"%s %d",url,count)!=EOF){
        if(strcmp(url,clurl) == 0){
            count++;
        }
        fprintf(out,"%s %d\n",url,count);

    }
    fclose(inp);
    fclose(out);
    remove(inp);
    rename(out,filename);

}
