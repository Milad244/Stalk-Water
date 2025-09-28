
    document.addEventListener('DOMContentLoaded', function() {
        clearCookiesOnce(); 
        navbar_setup();
        new_user_setup();
    });

    // This flag ensures cookies are cleared only once
    let cookiesCleared = false;
    function clearCookiesOnce() {
        if (cookiesCleared) return; // already done
        cookiesCleared = true;

        document.cookie.split(";").forEach(cookie => {
            const eqPos = cookie.indexOf("=");
            const name = eqPos > -1 ? cookie.substr(0, eqPos).trim() : cookie.trim();
            document.cookie = name + "=;expires=Thu, 01 Jan 1970 00:00:00 GMT;path=/";
        });
        console.log("Cookies cleared once.");
    }

    function navbar_setup(){
        const menuBtn = document.getElementById('menu-btn');
        const dropdown = document.getElementById('dropdown');

        // Toggle dropwdown on click
        menuBtn.addEventListener('click', () => {
            dropdown.style.display = dropdown.style.display === 'block' ? 'none' : 'block';
        });

        // Close dropdown when mouse leaves the dropdown area
        dropdown.addEventListener('mouseleave', () => {
            dropdown.style.display = 'none';
        });

        // (Optional) also close when mouse leaves the button itself
        menuBtn.addEventListener('mouseleave', () => {
        // Small delay so user can move from button → dropdown
        setTimeout(() => {
            if (!dropdown.matches(':hover')) {
                dropdown.style.display = 'none';
            }
        }, 300);
        });
    }

    function new_user_setup(){
        const existingUser = localStorage.getItem('user');

        const new_user_block = document.getElementById("new-user-block");
        new_user_block.classList.remove('hidden');
        const day_water_block = document.getElementById("day-water-block");
        day_water_block.classList.add('hidden');
        const main = document.getElementById("main-block");
        main.classList.add('hidden');

        if (existingUser) {
            const user = JSON.parse(existingUser);
            console.log("Loaded user from storage:", user);

            new_user_block.classList.add('hidden');
            day_water_block.classList.remove('hidden');
            main.classList.remove('hidden');
            console.log(day_water_block);

            document.getElementById('welcome-msg').textContent = `Welcome back, ${user.name}!`;
            return;
        }

        const form = document.getElementById('userForm');
        if (!form) return console.error("Form not found in DOM");

        form.addEventListener('submit', async (e) => {
            e.preventDefault();

            const userData = {
                name: document.getElementById('name').value,
                weight: document.getElementById('weight').value,
                gender: document.getElementById('gender').value
            };

            try {
                const response = await fetch('http://localhost:8080/users', {
                    method: 'POST',
                    headers: { 'Content-Type': 'application/json' },
                    body: JSON.stringify(userData)
                });

                const result = await response.json();
                console.log("Server response:", result);
            } catch (err) {
                console.error(err);
                result = {};
                console.log('Failed to reach backend');
            }
            localStorage.setItem('user', JSON.stringify(result));
                new_user_setup(); // reload page state
        });
    }
