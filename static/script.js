function updateNombre() {
    fetch('/api/nombre_personnes')
        .then(response => response.json())
        .then(data => {
            const container = document.getElementById('sallesContainer');
            container.innerHTML = "<h1>Nombre de personnes dans les salles :</h1>";  // Garde le titre

            if (!Array.isArray(data)) {
                console.error("Données reçues non valides :", data);
                return;
            }

            data.forEach(salle => {
                const div = document.createElement('div');
                div.className = 'carre';

                const salleName = document.createElement('span');
                salleName.className = 'salle-name';
                salleName.textContent = `${salle.id} :`;

                const nombrePersonnes = document.createElement('span');
                nombrePersonnes.className = 'nombre-personnes';
                nombrePersonnes.textContent = ` ${salle.nombre_personnes}`;

                div.appendChild(salleName);
                div.appendChild(nombrePersonnes);
                container.appendChild(div);
            });
        })
        .catch(error => {
            console.error("Erreur lors de la récupération des données", error);
            document.getElementById('sallesContainer').textContent = "Erreur de chargement";
        });
}

function searchRoom() {
    const input = document.getElementById('searchInput').value.toLowerCase();
    const rooms = document.querySelectorAll('.carre'); // Sélectionne toutes les salles

    rooms.forEach(room => {
        const roomName = room.querySelector('.salle-name').textContent.toLowerCase();
        if (roomName.includes(input)) {
            room.style.display = 'flex'; // Affiche la salle si elle correspond
        } else {
            room.style.display = 'none'; // Cache la salle sinon
        }
    });
}

// Mise à jour toutes les 1 secondes
updateNombre();
setInterval(updateNombre, 1000);

  
  
  

