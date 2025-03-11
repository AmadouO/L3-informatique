document.addEventListener("DOMContentLoaded", () => {
    const meteoOslo = document.querySelector("#meteo-oslo");
    const temperatureSpan = meteoOslo.querySelector(".temperature");
    const iconObject = meteoOslo.querySelector(".meteo-icon");
  
    const lat = 59.8939243;
    const lon = 10.6203135;
    const url = `https://api.met.no/weatherapi/locationforecast/2.0/compact?lat=${lat}&lon=${lon}`;
  
    fetch(url, {
      headers: { "User-Agent": "Mozilla/5.0" }, // Important pour éviter un refus de l'API
    })
      .then((response) => {
        if (!response.ok) {
          throw new Error(`Erreur API: ${response.status}`);
        }
        return response.json();
      })
      .then((data) => {
        const details = data.properties.timeseries[0].data.instant.details;
        const temperature = details.air_temperature;
        
        // Met à jour la température
        temperatureSpan.textContent = `${temperature}`;
  
        // Déterminer une icône météo simplifiée (ex: soleil, nuage, pluie)
        const symbol = data.properties.timeseries[0].data.next_1_hours?.summary.symbol_code || "unknown";
        //iconObject.data = `https://api.met.no/weatherapi/weathericon/2.0/legacysymbols?symbol=${symbol}`;
        iconObject.data = `weathericons/svg/${symbol}.svg`;

        console.log("Météo Oslo :", temperature, symbol);
      })
      .catch((error) => {
        console.error("Erreur lors de la récupération des données météo :", error);
        temperatureSpan.textContent = "N/A";
      });
  });

  //############################################################################################################

  document.addEventListener("DOMContentLoaded", async () => {
    await afficherMeteoLyon();
  });
  
  async function getCoordinates(city) {
    const url = `https://data.geopf.fr/geocodage/search?&q=${city}`;
    
    try {
      const response = await fetch(url);
      if (!response.ok) throw new Error(`Erreur API IGN: ${response.status}`);
      
      const data = await response.json();
      if (data.features.length === 0) throw new Error("Ville non trouvée");
  
      // ⚠️ L'API renvoie [longitude, latitude], on doit inverser !
      const [lon, lat] = data.features[0].geometry.coordinates;
      
      return { lat, lon };
    } catch (error) {
      console.error("Erreur récupération coordonnées :", error);
      return null;
    }
  }
  
  async function getMeteo(lat, lon) {
    const url = `https://api.met.no/weatherapi/locationforecast/2.0/compact?lat=${lat}&lon=${lon}`;
  
    try {
      const response = await fetch(url, { headers: { "User-Agent": "Mozilla/5.0" } });
      if (!response.ok) throw new Error(`Erreur API météo: ${response.status}`);
  
      return await response.json();
    } catch (error) {
      console.error("Erreur récupération météo :", error);
      return null;
    }
  }
  
  async function afficherMeteoLyon() {
    const meteoLyon = document.querySelector("#meteo-lyon");
    
    // 🔹 Récupérer les coordonnées de Lyon
    const coords = await getCoordinates("Lyon");
    if (!coords) {
      meteoLyon.innerHTML = "<p>Erreur lors de la récupération des coordonnées</p>";
      return;
    }
  
    const { lat, lon } = coords;
  
    // 🔹 Mettre à jour le HTML avec la ville et les coordonnées
    meteoLyon.innerHTML = `
      <h3><span class="ville">Lyon</span> <span class="coord">lat:${lat}, lon:${lon}</span></h3>
      <span class="temperature"></span>
      <object class="meteo-icon" type="image/svg+xml"></object>
    `;
  
    const temperatureSpan = meteoLyon.querySelector(".temperature");
    const iconObject = meteoLyon.querySelector(".meteo-icon");
  
    // 🔹 Récupérer la météo avec les coordonnées
    const meteoData = await getMeteo(lat, lon);
    if (!meteoData) {
      temperatureSpan.textContent = "N/A";
      return;
    }
  
    // 🔹 Extraire la température et le symbole météo
    const details = meteoData.properties.timeseries[0].data.instant.details;
    const temperature = details.air_temperature;
    const symbol = meteoData.properties.timeseries[0].data.next_1_hours?.summary.symbol_code || "unknown";
  
    // 🔹 Mettre à jour le DOM
    temperatureSpan.textContent = `${temperature}`;
    iconObject.data = `weathericons/svg/${symbol}.svg`;
  
    console.log(`Météo Lyon : ${temperature}°C, ${symbol}`);
  }

  //##############################################################################################

  document.addEventListener("DOMContentLoaded", async () => {
    await afficherMeteoVilles();
  });
  
  const villesFavorites = ["Paris", "Marseille", "Toulouse", "Villeurbanne", "Lille"];
  
  async function afficherMeteoVilles() {
    const dashboard = document.querySelector("#meteo-dashboard");
    const template = document.querySelector("#meteo-card-template");
  
    for (const ville of villesFavorites) {
      const coords = await getCoordinates(ville);
      if (!coords) continue;
  
      const { lat, lon } = coords;
      const meteoData = await getMeteo(lat, lon);
      if (!meteoData) continue;
  
      // Cloner le template
      const meteoCard = template.content.cloneNode(true);
      
      // Sélectionner les éléments du clone
      const villeSpan = meteoCard.querySelector(".ville");
      const coordSpan = meteoCard.querySelector(".coord");
      const temperatureSpan = meteoCard.querySelector(".temperature");
      const iconObject = meteoCard.querySelector(".meteo-icon");
  
      // Mettre à jour les données
      villeSpan.textContent = ville;
      coordSpan.textContent = `lat: ${lat.toFixed(2)}, lon: ${lon.toFixed(2)}`;
      
      const temperature = meteoData.properties.timeseries[0].data.instant.details.air_temperature;
      temperatureSpan.textContent = `${temperature}`;
      
      const symbol = meteoData.properties.timeseries[0].data.next_1_hours?.summary.symbol_code || "unknown";
      iconObject.data = `weathericons/svg/${symbol}.svg`;
  
      // Ajouter la fiche météo au tableau de bord
      dashboard.append(meteoCard);
      
      console.log(`Météo ${ville} : ${temperature}°C, ${symbol}`);
    }
  }
  
  