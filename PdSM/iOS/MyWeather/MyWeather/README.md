# Progetto iOS - MyWeather

### Requirements:
- Sviluppare un’applicazione per la visualizzazione della condizioni meteorologiche
- L’utente visualizza le condizioni meteorologiche attuali e previste per i prossimi N giorni nella sua posizione attuale
- L’utente inserisce una città e visualizza le condizioni meteorologiche attuali e previste per i prossimi N giorni
- L’utente può decidere di salvare la città come “preferita” ed aggiungerla ad una lista di città preferite per un accesso più rapido
- La lista delle città preferite può essere visualizzata su una mappa mettendo come marker un’icona legata alla condizione del meteo


## Sezioni (App Bar in Basso)
- Sezione Preferiti
  - Visualizzazione a Lista 
    - Button nella barra in alto che apre la visualizzazione a mappa
    - Icone negli elementi delle liste related al meteo
    - Temperatura come small tooltip
  - Visualizzazione a Mappa
    - Visualizzazione estesa (la stessa della sezione ricerca) a partire dai Marker della Mappa
    - Icone corrispondenti alla situazione meteorologica
- Sezione Ricerca
  - Text Field In alto per ricerca tramite nome città
  - I singoli item aprono una visualizzazione di dettaglio delle condizioni meteo
- My Position
  - Sezione di dettaglio con informazioni sul meteo nella posizione corrente
  
## Pagina di Dettaglio
- Meteo Corrente
  - Temperatura
  - Le condizioni (Icona e Descrizione)
  - Nome del luogo
  - Velocità e Direzione del Vento
  - Tramonto e Alba
- Previsioni future
  - 

## Impostazioni Possibili
- Dark Mode / Light Mode / Auto
- Degrees Measure System (F°/C°)
- Sezione About
<!--- N Giorni di Stima visualizzata-->

**Some Resources:**
- [Alert Dialog](https://stackoverflow.com/questions/4988564/how-to-implement-a-pop-up-dialog-box-in-ios)
- [Alert dialog Buttons](https://stackoverflow.com/questions/24022479/how-would-i-create-a-uialertview-in-swift/33340757#33340757)
- [Custom Accessory view in UITableCell](https://stackoverflow.com/questions/30708818/ios-xcodehow-to-add-accessory-view-to-custom-cell)
- [Refresh Contents Control](https://developer.apple.com/design/human-interface-guidelines/ios/controls/refresh-content-controls/)
- [Dark Mode Overrides](https://developer.apple.com/documentation/uikit/appearance_customization/supporting_dark_mode_in_your_interface/choosing_a_specific_interface_style_for_your_ios_app?language=objc)
  - [Stack Overflow](https://stackoverflow.com/questions/66391172/how-to-change-app-theme-light-dark-programmatically-in-swift-5)
- Use `NSNotificationManager` to broadcast Position updates

### OpenWeatherMap
  - https://openweathermap.org/api
  - https://openweathermap.org/api/one-call-api
  - https://openweathermap.org/current
