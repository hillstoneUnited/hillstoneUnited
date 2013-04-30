---
layout: layout
title: rcss3dSocketクラス
---
#rcss3dSocketクラス
##概要
ロボカップサーバーとの通信を、std::stringへ変換するクラスです。

サーバー付属のテストエージェント(rcssagent3d)の通信部分を一つのクラスへまとめたものです。  
グローバルスコープのmain関数部分と、通信部分を分けるためのクラス化です。

##不具合
サーバー接続時(コンストラクタおよびConnect関数)に使われているBindErrのtry-catchが  
うまく動いていないため、接続失敗時の処理が働いていません。  
    if(soc.Connect(port, host) == false){
      std::cout << "main: connect failed. exit program" << std::endl;
      exit(1);
    }
など

この問題のせいで接続先に指定されたサーバーが存在しなくても  
PutMessageなどを行うまでプログラムが停止しません。