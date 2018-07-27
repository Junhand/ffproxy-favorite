#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int import_data(char*);
int update_data(char*, char*);
int makehtml(char*);

int main(void) {
    //char *openhtml = "open loginscene.html";
    //system(openhtml);
    char url[256] = "https://webkaru.net/clang/file-fopen-fclose/" ;//url　http.cで取れる
    char id[16] = "192.168.2.102";//ipアドレス socket.cで取れる

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
int import_data(char *clip){
    FILE    *fp;
    char    filename[19];
    char    openhtml[26];

    sprintf(openhtml,"open %s.html",clip);//htmlfilenameをget

    /*最初のアクセス時に問答無用でこちらからhtmlを送り付ける*/
    makehtml(clip);//dbからhtmlファイル作成

    system(openhtml);//htmlファイルを開く
    return EXIT_SUCCESS;
}

/* クライアントのIPアドレス，URLへの接続回数をファイルに保存する．
 * 成功時には0を返す．
 * 失敗時には-1を返す．
 * 引数はIPアドレス,URLの各char型配列,
 */
int update_data(char *clip, char *clurl){
    FILE    *inp,*out;
    int     count;
    char    url[1000];
    char    filename[19];
    char    old[10] = "temp.txt";//一時的に作られるファイルの名前
    bool    flag = false;//これまでに見たことがある(dbにある)ページか判定.falseはみたことない
    int     one = 1;

    sprintf(filename,"%s.db",clip);
    inp = fopen(filename,"r+");//dbを開く
    out = fopen(old,"w+");//一時的にデータを入れるファイルを開く


    if(inp == NULL){//dbがなければ
          fprintf(out,"%s %d\n",clurl,one);//1つ目を入れる
    }else{
      while(fscanf(inp,"%s %d",url,&count)!=EOF){
        if(strcmp(url,clurl) == 0){
          count++;
          flag = true;//すでにみたことあるページ
        }
          fprintf(out,"%s %d\n",url,count);//dbをコピー
        }
        if(flag == false){
          fprintf(out,"%s %d\n",clurl,one);//
        }
    }
    fclose(inp);
    fclose(out);
    remove(filename);
    rename(old,filename);
    return EXIT_SUCCESS;
}


int makehtml(char *clip){
  FILE    *htmlfile,*dbfile;
  int     count;
  char    url[1024];
  char    filename[19];
  char    dbfilename[19];
  char    code[1024];

  sprintf(filename,"%s.html",clip);
  sprintf(dbfilename,"%s.db",clip);

  htmlfile = fopen(filename,"w+");
  dbfile = fopen(dbfilename,"r+");

    fprintf(htmlfile,"<!DOCTYPE html>\n");
    fprintf(htmlfile,"<html>\n");
    fprintf(htmlfile,"<head>\n");
    fprintf(htmlfile,"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n");
    fprintf(htmlfile,"<title>[TEST]ログイン画面</title>\n");
    fprintf(htmlfile,"</head>\n");
    fprintf(htmlfile,"<body>\n");
    fprintf(htmlfile,"<h1>お気に入り</h1>\n");
    while(fscanf(dbfile,"%s %d",url,&count)!=EOF){
      if(count >= 3){
        fprintf(htmlfile,"<a href=\"%s\">%s</a><br>\n",url,url);
      }
    }
    fprintf(htmlfile,"</body>\n");
    fprintf(htmlfile,"</html>\n");

  fclose(dbfile);
  fclose(htmlfile);
  return EXIT_SUCCESS;
}
