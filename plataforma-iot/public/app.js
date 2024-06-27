var temperaturePath = 'readings/temperature';
var humidityPath = 'readings/humidity';
var thresholdPath = 'readings/threshold'

const temperature = database.ref(temperaturePath);
const humidity = database.ref(humidityPath);
const threshold = database.ref(thresholdPath);

const button = document.getElementById("setTemperature");
var temperatureValue;
var humidityValue;
var thresholdValue;

temperature.on('value', (snapshot) => {
    temperatureValue = snapshot.val();
    console.log(temperatureValue);
    document.getElementById("temperature").innerHTML = temperatureValue;
}, (errorObject) => {
    console.log('The read failed: ' + errorObject.name);
});

humidity.on('value', (snapshot) => {
    humidityValue = snapshot.val();
    console.log(humidityValue);
    document.getElementById("humidity").innerHTML = humidityValue;
}, (errorObject) => {
    console.log('The read failed: ' + errorObject.name);
});

threshold.on('value', (snapshot) => {
    thresholdValue = snapshot.val();
    console.log(thresholdValue);
    document.getElementById("thresholdValue").innerHTML = thresholdValue;
}, (errorObject) => {
    console.log('The read failed: ' + errorObject.name);
});
function setTemperature() {

    var temp = document.getElementById("threshold").value;
    threshold.set(Number(temp))
}

button.addEventListener("click", setTemperature)