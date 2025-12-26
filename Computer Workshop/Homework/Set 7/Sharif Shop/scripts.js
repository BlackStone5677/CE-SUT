const products = [
    // ===== Renaissance & Baroque =====
    {
        id: 1,
        name: "Mona Lisa",
        description: "لئوناردو داوینچی – رنسانس",
        price: 500,
        image: "https://upload.wikimedia.org/wikipedia/commons/6/6a/Mona_Lisa.jpg"
    },
    {
        id: 2,
        name: "The Last Supper",
        description: "لئوناردو داوینچی – رنسانس",
        price: 480,
        image: "https://upload.wikimedia.org/wikipedia/commons/thumb/4/48/The_Last_Supper_-_Leonardo_Da_Vinci_-_High_Resolution_32x16.jpg/500px-The_Last_Supper_-_Leonardo_Da_Vinci_-_High_Resolution_32x16.jpg"
    },
    {
        id: 3,
        name: "The Night Watch",
        description: "رامبرانت – باروک",
        price: 460,
        image: "https://upload.wikimedia.org/wikipedia/commons/thumb/3/3a/La_ronda_de_noche%2C_por_Rembrandt_van_Rijn.jpg/500px-La_ronda_de_noche%2C_por_Rembrandt_van_Rijn.jpg"
    },

    // ===== 19th Century =====
    {
        id: 4,
        name: "The Gleaners",
        description: "ژان-فرانسوا میله – رئالیسم",
        price: 290,
        image: "https://upload.wikimedia.org/wikipedia/commons/thumb/1/1f/Jean-Fran%C3%A7ois_Millet_-_Gleaners_-_Google_Art_Project_2.jpg/500px-Jean-Fran%C3%A7ois_Millet_-_Gleaners_-_Google_Art_Project_2.jpg"
    },
    {
        id: 5,
        name: "Impression, Sunrise",
        description: "کلود مونه – امپرسیونیسم",
        price: 320,
        image: "https://upload.wikimedia.org/wikipedia/commons/thumb/5/59/Monet_-_Impression%2C_Sunrise.jpg/330px-Monet_-_Impression%2C_Sunrise.jpg"
    },
    {
        id: 6,
        name: "The Hay Wain",
        description: "جان کانستبل – رمانتیسیسم",
        price: 300,
        image: "https://upload.wikimedia.org/wikipedia/commons/thumb/5/5e/John_Constable_-_The_Hay_Wain_%281821%29.jpg/500px-John_Constable_-_The_Hay_Wain_%281821%29.jpg"
    },

    // ===== Post-Impressionism & Expressionism =====
    {
        id: 7,
        name: "Starry Night",
        description: "ونسان ون‌گوگ – پساامپرسیونیسم",
        price: 400,
        image: "https://upload.wikimedia.org/wikipedia/commons/thumb/e/ea/Van_Gogh_-_Starry_Night_-_Google_Art_Project.jpg/960px-Van_Gogh_-_Starry_Night_-_Google_Art_Project.jpg"
    },
    {
        id: 8,
        name: "The Yellow House",
        description: "ونسان ون‌گوگ – اثر کمتر دیده‌شده",
        price: 340,
        image: "https://upload.wikimedia.org/wikipedia/commons/thumb/7/7b/Vincent_van_Gogh_-_The_yellow_house_%28%27The_street%27%29.jpg/960px-Vincent_van_Gogh_-_The_yellow_house_%28%27The_street%27%29.jpg"
    },
    {
        id: 9,
        name: "Street, Dresden",
        description: "ارنست لودویگ کیرشنر – اکسپرسیونیسم",
        price: 310,
        image: "https://upload.wikimedia.org/wikipedia/commons/a/a2/Kirchner_-_Die_Stra%C3%9Fe.jpg"
    },

    // ===== Modern Art =====
    {
        id: 10,
        name: "Guernica",
        description: "پابلو پیکاسو – کوبیسم",
        price: 450,
        image: "https://upload.wikimedia.org/wikipedia/en/7/74/PicassoGuernica.jpg"
    },
    {
        id: 11,
        name: "Les Demoiselles d'Avignon",
        description: "پابلو پیکاسو – آغاز کوبیسم",
        price: 420,
        image: "https://upload.wikimedia.org/wikipedia/en/thumb/4/4c/Les_Demoiselles_d%27Avignon.jpg/960px-Les_Demoiselles_d%27Avignon.jpg?20081229135437"
    },
    {
        id: 12,
        name: "Composition VII",
        description: "واسیلی کاندینسکی – آبستره",
        price: 360,
        image: "https://upload.wikimedia.org/wikipedia/commons/thumb/0/01/Composition_VII_-_Wassily_Kandinsky%2C_GAC.jpg/960px-Composition_VII_-_Wassily_Kandinsky%2C_GAC.jpg"
    },

    // ===== Surrealism =====
    {
        id: 13,
        name: "The Persistence of Memory",
        description: "سالوادور دالی – سوررئالیسم",
        price: 380,
        image: "https://upload.wikimedia.org/wikipedia/en/d/dd/The_Persistence_of_Memory.jpg"
    },
    {
        id: 14,
        name: "The Elephant Celebes",
        description: "ماکس ارنست – سوررئالیسم (کمتر معروف)",
        price: 330,
        image: "https://upload.wikimedia.org/wikipedia/en/thumb/2/2b/The_Elephant_Celebes.jpg/609px-The_Elephant_Celebes.jpg?20100705235611"
    },

    // ===== Non-Western / Obscure =====
    {
        id: 15,
        name: "The Great Wave off Kanagawa",
        description: "هوکوسای – هنر ژاپن",
        price: 310,
        image: "https://upload.wikimedia.org/wikipedia/commons/thumb/a/a5/Tsunami_by_hokusai_19th_century.jpg/960px-Tsunami_by_hokusai_19th_century.jpg"
    },
    {
        id: 16,
        name: "Court of Gayumars",
        description: "مینیاتور ایرانی – شاهنامه شاه تهماسب",
        price: 350,
        image: "https://upload.wikimedia.org/wikipedia/commons/thumb/e/ec/The_Court_of_Gayumars.jpg/500px-The_Court_of_Gayumars.jpg?20200601071513"
    },

    // ===== 20th Century / Abstract =====
    {
        id: 17,
        name: "Broadway Boogie Woogie",
        description: "پیت موندریان – نئوپلاستیسیسم",
        price: 300,
        image: "https://upload.wikimedia.org/wikipedia/commons/thumb/3/30/Piet_Mondrian%2C_1942_-_Broadway_Boogie_Woogie.jpg/960px-Piet_Mondrian%2C_1942_-_Broadway_Boogie_Woogie.jpg"
    },
    {
        id: 18,
        name: "Black Square",
        description: "کازیمیر مالویچ – آوانگارد (نمادین و بحث‌برانگیز)",
        price: 270,
        image: "https://upload.wikimedia.org/wikipedia/commons/thumb/d/dc/Kazimir_Malevich%2C_1915%2C_Black_Suprematic_Square%2C_oil_on_linen_canvas%2C_79.5_x_79.5_cm%2C_Tretyakov_Gallery%2C_Moscow.jpg/330px-Kazimir_Malevich%2C_1915%2C_Black_Suprematic_Square%2C_oil_on_linen_canvas%2C_79.5_x_79.5_cm%2C_Tretyakov_Gallery%2C_Moscow.jpg"
    }
];

let cart = {};

const productList = document.getElementById("productList");
const cartItems = document.getElementById("cartItems");
const totalPriceEl = document.getElementById("totalPrice");
const sortSelect = document.getElementById("sortPrice");

function renderProducts(list) {
    productList.innerHTML = "";
    list.forEach(p => {
        productList.innerHTML += `
            <div class="product">
                <img src="${p.image}" alt="${p.name}">
                <h3>${p.name}</h3>
                <p>${p.description}</p>
                <p>$${p.price}</p>
                <button onclick="addToCart(${p.id})">Add to Cart</button>
            </div>
        `;
    });
}

function addToCart(id) {
    if (cart[id]) {
        cart[id].count++;
    } else {
        const product = products.find(p => p.id === id);
        cart[id] = { ...product, count: 1 };
    }
    renderCart();
}

function removeFromCart(id) {
    if (cart[id].count > 1) {
        cart[id].count--;
    } else {
        delete cart[id];
    }
    renderCart();
}

function renderCart() {
    cartItems.innerHTML = "";
    let total = 0;

    Object.values(cart).forEach(item => {
        total += item.price * item.count;
        cartItems.innerHTML += `
            <li>
                ${item.name} (${item.count})
                <button onclick="removeFromCart(${item.id})">Remove</button>
            </li>
        `;
    });

    totalPriceEl.textContent = total;
}

sortSelect.addEventListener("change", () => {
    let sorted = [...products];

    if (sortSelect.value === "asc") {
        sorted.sort((a, b) => a.price - b.price);
    } else if (sortSelect.value === "desc") {
        sorted.sort((a, b) => b.price - a.price);
    }

    renderProducts(sorted);
});

renderProducts(products);

const toggleBtn = document.getElementById("themeToggle");

toggleBtn.addEventListener("click", () => {
    document.body.classList.toggle("dark");

    // save preference
    if (document.body.classList.contains("dark")) {
        localStorage.setItem("theme", "dark");
        toggleBtn.textContent = "☀️";
    } else {
        localStorage.setItem("theme", "light");
        toggleBtn.textContent = "🌙";
    }
});

// load saved theme
if (localStorage.getItem("theme") === "dark") {
    document.body.classList.add("dark");
    toggleBtn.textContent = "☀️";
}
