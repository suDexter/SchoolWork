var video;
var display;
window.onload = function () {
    video = document.getElementById("videoPlayer");
    display = document.getElementById("displayStatus");
    video.onplaying = function () {
        display.innerHTML = "Playing......";
    }
    video.onpause = function () {
        display.innerHTML = "Pausing......";
    }
}
function pause(){
    video.pause();
}
function play(){
    video.play();
}
function progressUpdate() {
    flag = 1;
    var postionBar = document.getElementById("postionBar");
    postionBar.style.width = (video.currentTime / video.duration * 100) + "%";
    display.innerHTML = Math.round((video.currentTime * 100) / 100) + "sec";
}
function stop(){
    video.pause();
    video.currentTime = 0;
}
function speedUp(){
    video.play();
    video.playbackRate = 2;
}
function slowDown(){
    video.play();
    video.playbackRate = 0.5;                
}
function normalSpeed(){
    video.play();
    video.playbackRate = 1;    
}
/*function XPause() {
    if (Math.round((video.currentTime * 100) / 100) == 2){
        video.pause();
    }
}*/

/*
function timer() {
    var s = Math.round((video.currentTime * 100) / 100);
    var btn = document.getElementsByTagName("button")[0];
    var time = setInterval(function () {
            if (s==7) {
                video.pause();
            } else {
                btn.innerHTML = "经过" + s + "秒";
                btn.disabled = true;
            }
        },
        500);
}*/