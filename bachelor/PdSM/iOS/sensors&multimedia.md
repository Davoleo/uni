**Pacchetto Slide: 9**

# Core Motion
- `#import <CoreMotion/CoreMotion.h>`
- Usa block-based (lambda) interfaces
- Tipi di dati
  1. `CMAccelerometerData`
  2. `CMGyroData` (giroscopio)
  3. `CMMagnetometerData` (orientamento)
- `CMMotionManager`: oggetto che fa da tramite tra i servizi di CoreMotion e le app
  - Deve essere un singleton (una sola istanza per una app)
- 4 Tipi di motion
  1. raw accelerometer data
  2. raw gyroscope data
  3. raw magnetometer data
  4. processed device-motion data (include accelerazione, ratio di rotazione e altitudine)
- Il manager manda dei dati ad un intervallo fisso
- I dati di motion sono passatti in un block-based anonymous function che gestisce i dati
- ci sono i vari metodi `stop` per fermare gli aggiornamenti sui movimenti ottenuti dai sensori

# Multimedia: Audio
- Offre diversi framework per lavorare con l'audio su livelli diversi
  - Media Player: https://developer.apple.com/library/ios/documentation/MediaPlayer/Reference/MediaPlayer_Framework
  - AV Foundation: play and record audio con interfaccia OBj-C semplice
  - Audio Toolbox
  - Audio Unit
  - OpenAL

### Accessing iPod Library
- `MPMusicPlayerController` scopo di selezionare manualmente gli elemnti della libreria
- `#import <MediaPlayer/MediaPlayer.h>` (va anche linkato)
- 2 tipi di music player
  1. l'_application music player_ riproduce musica localmente nell'app
  2. l'_iPod music player_ utilizza l'app di iPod built-in e permette riproduzione in background
- Il player si può instanziare in questo modo: `MPMusicPlayerController* player = [MPMusicPlayerController applicationMusicPlayer];`
- A questo punto si possono costruire delle code di playback tramite: `setQueueWithQuery:` oppure tramite `setQueueWithItemCollection:`
- per avviare la riproduzione si usa il metodo: `play`
- **Managing Playback**
  - `play`
  - `pause`
  - `stop`
  - altri metodi...
  - `skipToNextItem`
  - `skipToBeginning`
  - `skipToPreviousItem`

### `MPMediaItem`
- un item dentro alla libreria 
- Identificato univocamente dentro alla libreria in modo che persista in diversi lanci dell'app
- Ci sono molti metadati (chiamate proprietà) che possono essere attribuiti a questi item
- Per accedere ad un item tramite le sue proprietà si usa un metodo: `valueForProperty:`

### `MPMediaQuery`
- Operazione di selezione in base a criteri di raggruppamento
- Restituisce una `MPMediaItemCollection` (array di media item)

### `MPMediaPickerController`
- Un controller specializzato che permette all'utente di navigare nella libreria dell'iPod per selezionare i media item
- Ha un delegate (`MPMediaPickerControllerDelegate`) che viene notificato quando l'utente selezione un media item oppure annulla la selezione
- _Nota: Di solito per questo controller viene presentato in modo modale_

### System Sound Services
- Sistemi di base per lavorare con l'audio (e.g. suoni di sistema, effetti di vibrazione)
- `#import <AudioToolbox/AudioToolbox.h>`
- I suoni devono essere
  - meno lunghi di 30 secondi
  - in formato linear PCM oppure IMA4(IMA/ADPCM)
  - .caf, .aif o .wav file
- `AudioServicesPlaySystemSound(kSystemSoundID_Vibrate)`

### `AVAudioPlayer`
- `#import <AVFoundation/AVFoundation.h>`
- File di lunghezza arbitraria da riprodurre senza necessità speciali o elaborazionid a dover fare
- Questo player può:
  - Looppare audio
  - Più file contemporaneamente (senza speciale sincronizzazione)
  - Cambiare il volume
  - Possibile fare il seeking all'interno dell'audio
  - Informazioni sulla potenza del segnale audio
- C'è anche un `AVAudioPlayerDelegate` ogni volta che si verificano eventi speciali con questo audio
  
### `AVAudioRecorder`
- metodi per registrazione
- Si possono:
  - Registrare finché l'utente non ferma la registrazione
  - Registrare per una durata specifica
  - Mettere in pausa una registrazione e riprenderla
  - Ottenere audio input level data
Esempio:
```objective-c
/*Set Parameters */
[[AVAudioSession sharedInstance] setCategory:AVAudioSessionCategoryRecord error:nil];
[[AVAudioSession sharedInstance] setMode:AVAudioSessionModeVideoRecording error:nil];
[[AVAudioSession sharedInstance] setActive:YES error:nil];
/* get The url of audio file */
AVAudioRecorder* recorder [[AVAudioRecorder alloc] initWithURL:url settings:settings error:nil];

[recorder record];
```

### Video Playback
- `MPMoviePlayerController`
- Riprodurre video che derivano da file o da stream di rete
- si può piazzare o a schermo intero o minimizzato
- Supporta AirPlay per device come AppleTV
- Diverse proprietà:
  - `allowsAirPlay`
  - `setFullscreen:animated`
  - `controlStyle`: Stile dei controlli di playback
  - `initialPlaybackTime` inizio della finestra di riproduzione
  - `endPlaybackTime` fine della finestra di riproduzione
- Notifiche generate
  - `MPMoviePlayerPlaybackStateDidChangeNotification`
  - `MPMoviePlayerContentPreloadDidFinishNotification`
  - `MPMoviePlayerDidEnterFullscreenNotification`/`MPMoviePlayerDidExitFullscreenNotification`
- Esempio sulle slide

### Taking Pictures and videos
- Procedura standard di 3 passi
  1. Creare e presentare l'interfaccia della fotocamera (`UIImagePickerController`)
  2. L'utente scatta voto o registra video oppure annulla
  3. il controller notifica il risultato dell'operazione
Condizioni required:
- Il device deve avere una fotocamera (se è essenziale per l'app deve essere inserito nella lista delle capability necessarie)
- La fotocamera deve essere disponibile `isSourceTypeAvailable:`
- Un oggetto delegato conforme ai protocolli `UIImagePickerControllerDelegate` e `UINavigationControllerDelegate` per rispondere all'interazione utente

### Selezione foto e video dalla libreria
- Sempre con solito pickerController, ma con una sourceType di tipo:
  - UIImagePickerControllerSourceTypePhotoLibrary (accede a tutte le foto della libreria)
  - UIImagePickerControllerSourceTypeSavedPhotosAlbum (accede alla Camera Roll album only)