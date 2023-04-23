const recognition = new webkitSpeechRecognition();
recognition.continuous = true; // to enable continuous speech recognition
recognition.interimResults = false; // Only return final results
recognition.maxAlternatives = 5; // Increase maximum number of alternatives
recognition.lang = 'en-US';

const startBtn = document.getElementById('start');
const stopBtn = document.getElementById('stop');
const transcript = document.getElementById('transcript');

startBtn.addEventListener('click', () => {
  recognition.start();
});

stopBtn.addEventListener('click', () => {
    recognition.stop();
  });

recognition.onresult = (event) => {
  const resultIndex = event.resultIndex;
  const transcript = event.results[resultIndex][0].transcript;
  document.getElementById('transcript').value += transcript;
  console.log(transcript);
}
