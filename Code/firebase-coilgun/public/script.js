function rotateClockHands() {
  const now = new Date();
  const seconds = now.getSeconds();
  const minutes = now.getMinutes();
  const hours = now.getHours();

  const secondHand = document.querySelector(".second-hand");
  const minuteHand = document.querySelector(".minute-hand");
  const hourHand = document.querySelector(".hour-hand");

  const secondRotation = seconds * 6;
  const minuteRotation = (minutes * 6) + (seconds * 0.1);
  const hourRotation = (hours * 30) + (minutes * 0.5);

  secondHand.style.transform = `rotate(${secondRotation}deg)`;
  minuteHand.style.transform = `rotate(${minuteRotation}deg)`;
  hourHand.style.transform = `rotate(${hourRotation}deg)`;
}

setInterval(rotateClockHands, 1000);