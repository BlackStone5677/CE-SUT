function validateForm() {
    let id = document.getElementById("student_id").value;
    let error = document.getElementById("error");

    if (id === "") {
        error.innerText = "لطفاً شماره دانشجویی را وارد کنید.";
        return false;
    }

    error.innerText = "";
    return true;
}
