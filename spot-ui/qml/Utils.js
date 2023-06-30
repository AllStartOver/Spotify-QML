function formatTime(time) {
  var minutes = Math.floor(time / 60)
  var seconds = time % 60

  return minutes + ":" + (seconds < 10 ? "0" + seconds : seconds)
}

function QMLPath(fileName)
{
  return "qrc:/spotify-qml/imports/Views/qml/" + fileName
}

function ImagePath(fileName)
{
  return "qrc:/spotify-qml/imports/Images/" + fileName 
}
