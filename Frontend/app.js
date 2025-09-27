
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
