struct dico_t {
  char nom[64]; // On stock le nom du lexem
  char exp_str[256]; // Ici l'expression regulière en forme de chaine de caractères
  struct link_t * exp_file; // Ici l'expression regulière est en forme de list de char group
};

queue_t lire_fichier_conf(queue_t dictionnaire);
