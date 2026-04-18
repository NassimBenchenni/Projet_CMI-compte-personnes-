DROP TABLE IF EXISTS salle;

CREATE TABLE salle (
    id_num INT,
    id VARCHAR(255) PRIMARY KEY,
    nombre_personnes INT
);

INSERT INTO salle (id_num, id, nombre_personnes) VALUES (1, 'ELECTRONIQUE CC 133 B', 0);
INSERT INTO salle (id_num, id, nombre_personnes) VALUES (2, 'RESEAUX S7 132', 0);
INSERT INTO salle (id_num, id, nombre_personnes) VALUES (3, 'RESEAUX S8 132', 0);
INSERT INTO salle (id_num, id, nombre_personnes) VALUES (4, 'RESEAUX S9 132', 0);
INSERT INTO salle (id_num, id, nombre_personnes) VALUES (5, 'RESEAUX S10 132', 10);
INSERT INTO salle (id_num, id, nombre_personnes) VALUES (6, 'stat9 = info - c 026', 0);
INSERT INTO salle (id_num, id, nombre_personnes) VALUES (7, 's2 = c 040', 0);
INSERT INTO salle (id_num, id, nombre_personnes) VALUES (8, 'elec = c 133b electronique', 0);
INSERT INTO salle (id_num, id, nombre_personnes) VALUES (9, 'stat 8 = info - c 127', 0);
INSERT INTO salle (id_num, id, nombre_personnes) VALUES (10, 'stat 7 = info - c 128', 0);
INSERT INTO salle (id_num, id, nombre_personnes) VALUES (11, 'stat 6 = info - c 129', 0);
INSERT INTO salle (id_num, id, nombre_personnes) VALUES (12, 'stat 5 = info - c 130', 0);
INSERT INTO salle (id_num, id, nombre_personnes) VALUES (13, 'stat 4 = info - c 131', 0);
INSERT INTO salle (id_num, id, nombre_personnes) VALUES (14, 'stat 3 = info - c 135', 0);
INSERT INTO salle (id_num, id, nombre_personnes) VALUES (15, 'stat 2 = info - c 136', 0);
INSERT INTO salle (id_num, id, nombre_personnes) VALUES (16, 'stat 1 = info - c 137', 0);
INSERT INTO salle (id_num, id, nombre_personnes) VALUES (17, 's8 = c 030', 0);
INSERT INTO salle (id_num, id, nombre_personnes) VALUES (18, 's7 = c 032', 0);
INSERT INTO salle (id_num, id, nombre_personnes) VALUES (19, ' s6 = c 022 ', 0);
INSERT INTO salle (id_num, id, nombre_personnes) VALUES (20, ' s5 = c 024 ', 0);
INSERT INTO salle (id_num, id, nombre_personnes) VALUES (21, ' amphi ada ', 0);
INSERT INTO salle (id_num, id, nombre_personnes) VALUES (22, ' s2 bis = c 038 ', 0);
INSERT INTO salle (id_num, id, nombre_personnes) VALUES (23, ' s4 = c 034 ', 0);
INSERT INTO salle (id_num, id, nombre_personnes) VALUES (24, ' s3 = c 036 ', 0);
INSERT INTO salle (id_num, id, nombre_personnes) VALUES (25, ' amphi blaise ', 0);
INSERT INTO salle (id_num, id, nombre_personnes) VALUES (26, ' s1 = c 042 nodes ', 0);
INSERT INTO salle (id_num, id, nombre_personnes) VALUES (27, ' rob = c 134 robotique     ', 0);
INSERT INTO salle (id_num, id, nombre_personnes) VALUES (28, ' res = c 132 reseaux ', 0);
INSERT INTO salle (id_num, id, nombre_personnes) VALUES (29, ' cisco = c 133 réseaux ', 0);
