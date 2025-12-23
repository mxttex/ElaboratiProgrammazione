# 📂 Riepilogo Test Automatici - Gruppo 24
### Valutazione Finale: 29/30 (due punti in piu allo scritto)

Di seguito il dettaglio degli esiti per ogni elaborato sottoposto alla suite di test.

## 📊 Tabella Risultati

| Elaborato | Argomento | Esito | Note |
| :--- | :--- | :---: | :--- |
| **Elab 2** | Funzioni Quadratiche | ✅ PASS | Radici ed estremi corretti |
| **Elab 3** | Manipolazione Interi | ✅ PASS | Splitting e riordino cifre corretti |
| **Elab 4** | Teoria dei Numeri | ✅ PASS | Primalità, n-esimo primo, co-primi |
| **Elab 5** | Conversione Basi | ✅ PASS | Conversioni (binaria, ternaria, ecc.) |
| **Elab 6** | Pong | ✅ PASS | Logica Pong (collisioni e punteggio) |
| **Elab 7** | Campo Minato | ✅ PASS | Generazione board e conteggio mine |
| **Elab 8** | AI Ghost (Pacman) | ⚠️ WARN | **2 Errori su casi speciali (su 2000 casi)** |
| **Elab 9** | Strutture Dati (Snake) | ✅ PASS | Gestione nodi/liste (7/7 superati) |
| **Elab 10** | Big Int Math | ✅ PASS | Moltiplicazione grandi numeri |

---

## ⚠️ Analisi Errori: Elaborato 8
L'elaborato 8 presenta anomalie nella gestione dei movimenti speciali (probabilmente legati ai tunnel o ai bordi della mappa).

**Dettaglio Anomalie:**

1.  **Test Case 2 (Wrapping/Teletrasporto):**
    * *Posizione Attuale:* `[14,0]`
    * *Posizione Attesa:* `[14,27]`
    * *Nota:* Errore significativo nella gestione del passaggio attraverso i bordi (Y=0 vs Y=27).

2.  **Test Case 3 (Adiacenza):**
    * *Posizione Attuale:* `[29,7]`
    * *Posizione Attesa:* `[29,8]`
    * *Nota:* Errore di calcolo della cella target (off-by-one).

