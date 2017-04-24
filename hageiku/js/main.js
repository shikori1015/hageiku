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
setReady();
//初期化設定
function setReady(){
    pow = 50;
    ex = 1;
    money = 1000;
    HPcount();
}
function HPcount(){
    document.getElementById("status").innerHTML = "精力:" + pow + "<br>経験値:" + ex + "<br>お金:" + money + "円";
    document.getElementById("level").innerHTML = "レベル:" + Math.floor(ex/50);
    document.getElementById('charaimag').src = img[Math.ceil(ex/500)].src;
    reRoad();
}
function reRoad(){
    setTimeout(HPcount,100)
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