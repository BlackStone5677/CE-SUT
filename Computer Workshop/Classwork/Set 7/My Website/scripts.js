const header = document.getElementById("profile");
const btn = document.getElementById("toggleBtn");

btn.addEventListener("click", () => {
    header.classList.toggle("dark");

    if (header.classList.contains("dark")) {
        btn.textContent = "تغییر به مشکی/سفید";
    }
});
