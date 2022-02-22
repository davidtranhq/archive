function init()
{
    name = prompt("Username:");
    document.getElementById("name").innerHTML = name + "-";
    
    canv = document.getElementById("gameCanvas");
    canv.width = window.innerWidth;
    canv.height = window.innerHeight;
    ctx = canv.getContext("2d");
    
    setInterval(update, 1000);
}

function update()
{
    ctx.font = "32px Pixeled";
    ctx.fillStyle = "Green";
    
}