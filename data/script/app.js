
let mqttClient = null;

document.addEventListener('DOMContentLoaded', function() {
    document.getElementById('connect-btn').addEventListener('click', connectToBroker);
    document.getElementById('disconnect-btn').addEventListener('click', disconnectFromBroker);
});

function connectToBroker() {
    const brokerUrl = document.getElementById('broker-url').value;
    const topic = document.getElementById('topic').value;
    
    // Options untuk koneksi MQTT
    const options = {
        keepalive: 60,
        clientId: 'memet' + Math.random().toString(16).substr(2, 8),
        protocolId: 'MQTT',
        protocolVersion: 4,
        clean: true,
        reconnectPeriod: 1000,
        connectTimeout: 30 * 1000,
    };
    
    try {
        mqttClient = mqtt.connect(brokerUrl, options);
        
        mqttClient.on('connect', () => {
            updateConnectionStatus('Connected');
            document.getElementById('connect-btn').disabled = true;
            document.getElementById('disconnect-btn').disabled = false;
            
            mqttClient.subscribe(topic, { qos: 0 }, (err) => {
                if (err) {
                    console.error('Subscription error:', err);
                    updateDataContainer(`Error subscribing: ${err.message}`);
                } else {
                    updateDataContainer(`Subscribed to topic: ${topic}`);
                }
            });
        });
        
        mqttClient.on('message', (receivedTopic, message) => {
            const data = parseMessage(message.toString());
            displayData(data, receivedTopic);
        });
        
        mqttClient.on('error', (err) => {
            console.error('Connection error:', err);
            updateConnectionStatus(`Error: ${err.message}`);
        });
        
        mqttClient.on('close', () => {
            updateConnectionStatus('Disconnected');
            document.getElementById('connect-btn').disabled = false;
            document.getElementById('disconnect-btn').disabled = true;
        });
        
        mqttClient.on('reconnect', () => {
            updateConnectionStatus('Reconnecting...');
        });
        
    } catch (err) {
        console.error('MQTT initialization error:', err);
        updateDataContainer(`Error: ${err.message}`);
    }
}

function disconnectFromBroker() {
    if (mqttClient && mqttClient.connected) {
        mqttClient.end();
        updateConnectionStatus('Disconnected');
        document.getElementById('connect-btn').disabled = false;
        document.getElementById('disconnect-btn').disabled = true;
    }
}

function parseMessage(message) {
    try {
        return JSON.parse(message);
    } catch (e) {
        return message; // Return as plain text if not JSON
    }
}

function displayData(data, topic) {
    const container = document.getElementById('data-container');
    const now = new Date().toLocaleTimeString();
    
    if (typeof data === 'object' && data !== null) {
        let html = `<div class="message"><small>${now} - ${topic}</small>`;
        for (const [key, value] of Object.entries(data)) {
            html += `<div class="data-item">
                <span class="sensor-label">${key}:</span> 
                <span class="sensor-value">${value}</span>
            </div>`;
        }
        html += '</div>';
        container.insertAdjacentHTML('afterbegin', html);
    } else {
        container.insertAdjacentHTML('afterbegin', 
            `<div class="message"><small>${now} - ${topic}</small>
             <div class="data-item">${data}</div></div>`);
    }
}

function updateConnectionStatus(status) {
    document.getElementById('connection-status').textContent = `Status: ${status}`;
}

function updateDataContainer(message) {
    const container = document.getElementById('data-container');
    container.insertAdjacentHTML('afterbegin', `<div class="message">${message}</div>`);
}