function formatTime(time) {
  var minutes = Math.floor(time / 60)
  var seconds = time % 60

  return minutes + ":" + (seconds < 10 ? "0" + seconds : seconds)
}