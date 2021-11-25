// file-input
const formInputs = document.getElementsByClassName("file");
const length = formInputs.length;
for (let i = 0; i < length; i++) {
    formInputs[i].onchange = function () {
        const file = this.files[0].name;
        const label = this.nextElementSibling;
        if (!label.classList.contains("changed")) {
            const span = document.createElement("span");
            span.className = "filename";
            this.parentNode.appendChild(span);
            label.classList.add("changed");
        }
        label.nextElementSibling.innerHTML = file;
    };
}

// mac address hexadecimal -> decimal
function dec() {
    let val = document.querySelectorAll("input[name='mac']");
    val.forEach(function(elem){
        let hex = elem.value;
        let decimal = parseInt(hex,16);
        elem.value = decimal;
    });
}

function hex() {
    let val = document.querySelectorAll("input[name='mac']");
    val.forEach(function(elem){
        let decimal = parseInt(elem.value);
        let hex = decimal.toString(16).toUpperCase();
        elem.value = hex;
    });
}

window.onload = function () {
    let elmbtn = document.getElementById('btn');
    elmbtn.onclick = function () {
        if (this.checked == true) {
            hex();
        } else {
            dec();
        }
    }

    let expbtn = document.getElementById('export');
    expbtn.onclick = function () {
        if (elmbtn.checked == true) {
            elmbtn.checked = false;
            dec();
        }
    }
}