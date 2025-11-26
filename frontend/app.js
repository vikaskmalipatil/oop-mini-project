const API = "http://localhost:8080";

function addUser() {
    const name = document.getElementById("u_name").value;
    const age = document.getElementById("u_age").value;
    const height = document.getElementById("u_height").value;
    const weight = document.getElementById("u_weight").value;

    fetch(`${API}/addUser?name=${name}&age=${age}&height=${height}&weight=${weight}`,
          { method: "POST" })
    .then(r => r.text())
    .then(t => document.getElementById("userOut").innerText = t);
}

function addWorkout() {
    const name = document.getElementById("w_name").value;
    const type = document.getElementById("w_type").value;
    const duration = document.getElementById("w_duration").value;
    const calories = document.getElementById("w_calories").value;

    fetch(`${API}/addWorkout?name=${name}&type=${type}&duration=${duration}&calories=${calories}`,
          { method: "POST" })
    .then(r => r.text())
    .then(t => document.getElementById("workOut").innerText = t);
}

function getStats() {
    const name = document.getElementById("s_name").value;

    fetch(`${API}/stats?name=${name}`)
        .then(r => r.text())
        .then(t => document.getElementById("statsOut").innerText = t);
}
