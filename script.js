function startGame(){
    window.location.href = "index.html";
}
function reload(){
    window.location.href = "startGame.html";
}
const startGame = async () => {
  await fetch("http://localhost:3001/start", {
    method: "POST",
  });

  const interval = setInterval(async () => {
    const response = await fetch("http://localhost:3001/result");
    const data = await response.json();

    if (data.reactionTime) {
      setReactionTime(data.reactionTime);
      clearInterval(interval);
    }
  }, 500);
};