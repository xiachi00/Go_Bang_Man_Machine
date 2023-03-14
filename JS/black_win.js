var result = confirm('玩家获胜！\n\n是否回到主页重启游戏？');
if (result) {
    location.href = "http://150.158.146.95:8888/";
} else {
    location.href = "http://150.158.146.95:8888/back.html";
}