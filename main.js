img = new Array();
img[1] = new Image();
img[1].src = "./images/c000_0.png";
img[2] = new Image();
img[2].src = "./images/c001_0.png";
img[3] = new Image();
img[3].src = "./images/c002_0.png";
img[4] = new Image();
img[4].src = "./images/c003_0.png";
img[5] = new Image();
img[5].src = "./images/c004_0.png";
img[6] = new Image();
img[6].src = "./images/c005_0.png";
img[7] = new Image();
img[7].src = "./images/c006_0.png";
img[8] = new Image();
img[8].src = "./images/c007_0.png";
img[9] = new Image();
img[9].src = "./images/c008_0.png";
img[10] = new Image();
img[10].src = "./images/c009_0.png";
img[11] = new Image();
img[11].src = "./images/c100_0.png";
img[12] = new Image();
img[12].src = "./images/c101_0.png";
img[13] = new Image();
img[13].src = "./images/c102_0.png";
//初期化設定
function setReady(){
    pow = 50;
    ex = 1;
    money = 1000;
    pow_old = 0;
    ex_old = 0;
    money_old = 0;
    n = 1;
    gohan_count = 0;
    oshigoto_count = 0;
    setting_count = 0;
    HPcount();
}
function HPcount(){
    if(pow != pow_old || ex != ex_old || money != money_old){
        pow_old = pow;
        ex_old = ex;
        money_old = money;
        /*▼デバックのせいでコメントされた部分ここから*/
        n = Math.ceil(ex/50);
        /*▼デバックのせいでコメントされた部分ここまで*/
        pow = 50 + n - 1; 
        document.getElementById("status").innerHTML = "精力:" + pow + "<br>経験値:" + (ex-1) + "<br>お金:" + money + "円";
        document.getElementById("level").innerHTML = "レベル:" + n;
        document.getElementById('charaimag').src = img[Math.ceil(n/10)].src;
        /*▼デバックのせいでコメントアウトされた部分ここから
        if(ex>=Math.pow(10,n)){
            n ++;
        }▲デバックのせいでコメントアウトされた部分ここまで*/
        if(n <= 10){
            document.getElementById("name").innerHTML = "ハゲヤマ";
        }else if(11 <= n && n <= 20){
            document.getElementById("name").innerHTML = "ジャスティス";
        }else if(21 <= n && n <= 30){
            document.getElementById("name").innerHTML = "ナマハゲ";
        }else if(31 <= n && n <= 40){
            document.getElementById("name").innerHTML = "キョウトウ";
        }else if(41 <= n && n <= 50){
                        document.getElementById("name").innerHTML = "不毛";
        }else if(51 <= n && n <= 60){
            document.getElementById("name").innerHTML = "不耕作地";
        }else if(61 <= n && n <= 70){
            document.getElementById("name").innerHTML = "チカンのハゲ";
        }else if(71 <= n && n <= 80){
            document.getElementById("name").innerHTML = "オヤノハゲヒカリ";
        }else if(81 <= n && n <= 90){
            document.getElementById("name").innerHTML = "カッパ";
        }else{
            document.getElementById("name").innerHTML = "アタマスゴクヒカルハゲ";
        }
    }
    reRoad();
}
function reRoad(){
    setTimeout(HPcount,100);
}
function plusmoney(){
    money += 100;
}
            function plusex(){
                ex += 10;
            }
            function pluspow(){
                pow += 10;
            }
function gohan(){
    if(gohan_count == 1){
        gohan_count = 0;
        oshigoto_count = 0;
        setting_count = 0;
        document.getElementById('gohan_tr').style.display="none";
        document.getElementById('oshigoto_tr').style.display="none";
        document.getElementById('setting_tr').style.display="none";
    }else if(gohan_count == 0){
        gohan_count ++;
        oshigoto_count = 0;
        setting_count = 0;
        document.getElementById('gohan_tr').style.display="";
        document.getElementById('oshigoto_tr').style.display="none";
        document.getElementById('setting_tr').style.display="none";
    }
}
function oshigoto(){
    if(oshigoto_count == 1){
        gohan_count = 0;
        oshigoto_count = 0;
        setting_count = 0;
        document.getElementById('gohan_tr').style.display="none";
        document.getElementById('oshigoto_tr').style.display="none";
        document.getElementById('setting_tr').style.display="none";
    }else if(oshigoto_count == 0){
        oshigoto_count ++;
        gohan_count = 0;
        setting_count = 0;
        document.getElementById('gohan_tr').style.display="none";
        document.getElementById('oshigoto_tr').style.display="";
        document.getElementById('setting_tr').style.display="none";
    }
}
function setting(){
    if(setting_count == 1){
        setting_count = 0;
        gohan_count = 0;
        oshigoto_count = 0;
        document.getElementById('gohan_tr').style.display="none";
        document.getElementById('oshigoto_tr').style.display="none";
        document.getElementById('setting_tr').style.display="none";
    }else if(setting_count == 0){
        setting_count ++;
        gohan_count = 0;
        oshigoto_count = 0;
        document.getElementById('gohan_tr').style.display="none";
        document.getElementById('oshigoto_tr').style.display="none";
        document.getElementById('setting_tr').style.display="";
    }
}