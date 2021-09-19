struct dico_t {
  char nom[64];
  char exp_str[256];
  struct link_t * exp_file;
};

queue_t lire_fichier_conf(queue_t dictionnaire);
