import sqlite3

DB_NAME = "salle.db"

def update_people_count(room_id: int, new_count: int):
    """Met à jour le nombre de personnes dans une salle."""
    try:
        conn = sqlite3.connect(DB_NAME)
        cursor = conn.cursor()
        cursor.execute("UPDATE salle SET nombre_personnes = ? WHERE id_num = ?", (new_count, room_id))
        conn.commit()
        if cursor.rowcount > 0:
            print(f"Mise à jour réussie: Salle {room_id} -> {new_count} personnes")
        else:
            print(f"Échec: Aucune salle avec id_num {room_id}")
    except sqlite3.Error as e:
        print(f"Erreur SQLite: {e}")
    finally:
        conn.close()

def add_one(room_id: int):
    """Ajoute une personne dans la salle spécifiée."""
    try:
        conn = sqlite3.connect(DB_NAME)
        cursor = conn.cursor()
        cursor.execute("SELECT nombre_personnes FROM salle WHERE id_num = ?", (room_id,))
        result = cursor.fetchone()
        if result is not None:
            new_count = result[0] + 1
            print(f"Ajout d'une personne dans la salle {room_id}. Nouveau nombre: {new_count}")
            update_people_count(room_id, new_count)
        else:
            print(f"Aucune salle avec id_num {room_id}")
    except sqlite3.Error as e:
        print(f"Erreur SQLite: {e}")
    finally:
        conn.close()

def minus_one(room_id: int):
    """Retire une personne de la salle spécifiée."""
    try:
        conn = sqlite3.connect(DB_NAME)
        cursor = conn.cursor()
        cursor.execute("SELECT nombre_personnes FROM salle WHERE id_num = ?", (room_id,))
        result = cursor.fetchone()
        if result is not None:
            new_count = result[0] - 1 if result[0] > 0 else 0
            print(f"Retrait d'une personne dans la salle {room_id}. Nouveau nombre: {new_count}")
            update_people_count(room_id, new_count)
        else:
            print(f"Aucune salle avec id_num {room_id}")
    except sqlite3.Error as e:
        print(f"Erreur SQLite: {e}")
    finally:
        conn.close()
