from flask import Flask, jsonify, render_template, send_from_directory, request
import sqlite3
from update import add_one, minus_one  # Importation de vos fonctions

app = Flask(__name__)

# Fonction pour récupérer toutes les salles
def get_salles():
    conn = sqlite3.connect("salle.db")  # Ouvre la base de données
    cursor = conn.cursor()
    
    cursor.execute("SELECT id, nombre_personnes FROM salle")  # Récupère toutes les salles
    salles = [{"id": row[0], "nombre_personnes": row[1]} for row in cursor.fetchall()]
    
    conn.close()  # Ferme la connexion
    return salles

# Route pour servir le fichier HTML
@app.route('/')
def index():
    return send_from_directory('.', 'index.html')  # Sert le fichier HTML

# API qui retourne toutes les salles
@app.route('/api/nombre_personnes', methods=['GET'])
def api_nombre_personnes():
    return jsonify(get_salles())  # Renvoie un tableau JSON

# Nouvelle API pour mettre à jour une salle
@app.route('/api/update', methods=['POST'])
def api_update():
    """
    Reçoit un JSON avec "room_id" et "operation" (1 pour ajouter, 0 pour retirer).
    Exemple de JSON attendu : {"room_id": 1, "operation": 1}
    """
    data = request.get_json()
    if not data:
        return jsonify({"error": "Données manquantes"}), 400

    room_id = data.get('room_id')
    operation = data.get('operation')

    if room_id is None or operation is None:
        return jsonify({"error": "room_id ou operation manquant"}), 400

    if operation == 1:
        add_one(room_id)
    elif operation == 0:
        minus_one(room_id)
    else:
        return jsonify({"error": "Operation invalide, utilisez 0 ou 1"}), 400

    return jsonify({"message": "Mise à jour effectuée"}), 200

@app.route('/static/server.ico')
def favicon():
    return send_from_directory('.', 'server.ico', mimetype='image/vnd.microsoft.icon')

if __name__ == '__main__':
    app.run(host="0.0.0.0", port=5000, debug=True)
