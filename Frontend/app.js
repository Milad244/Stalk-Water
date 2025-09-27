
document.addEventListener('DOMContentLoaded', function() {
    navbar_setup();
});

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
    }, 200);
    });
}

function new_user_setup(){
    const existingUser = localStorage.getItem('user');

    if (existingUser) {
        const user = JSON.parse(existingUser);
        console.log("Loaded user from storage:", user);

        const new_user_block = document.getElementsById("new-user-block");
        const day_water_block = document.getElementById("day-water-block");

        new_user_block.classList.add('hidden');
        day_water_block.classList.remove('hidden');

        document.body.innerHTML = `
        <h2>Welcome back, ${user.name}!</h2>
        <p>Weight: ${user.weight}kg</p>
        <p>Gender: ${user.gender}</p>
        `;
        return;
    }
    const form = document.getElementById('userForm');

    form.addEventListener('submit', async (e) => {
        e.preventDefault();

        const userData = {
            name: document.getElementById('name').value,
            weight: document.getElementById('weight').value,
            gender: document.getElementById('gender').value,
        };

        try {
            const response = await fetch('http://localhost:8080/users', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify(userData),
            });

            const result = await response.text();
            console.log("Server response:", result);

            localStorage.setItem('user', JSON.stringify(result.data));
            new_user_setup();
        } catch (err) {
            console.error(err);
            alert('Failed to reach backend');
        }
    });
}
