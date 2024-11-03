import requests
import json
from typing import List, Dict

BASE_URL = "https://apidata-338754564953.europe-west9.run.app"
DATA_ENDPOINTS = {
    "csnj": "/api/implantation/csnj",
    "cirfa": "/api/implantation/cirfa",
    "smv": "/api/implantation/smv",
    "epide": "/api/implantation/epide",
    "e2c": "/api/implantation/e2c",
    "bases_defense": "/api/implantation/bases_defense",
    "cfa": "/api/education/cfa",
    "lycees": "/api/education/lycees",
    "enseignement_superieur": "/api/education/enseignement_superieur",
    "structures_retour_ecole": "/api/education/structures_retour_ecole",
    "stationnements": "/infrastructures/stationnements",
    "gares": "/infrastructures/gares"
}
def get_flat_data() -> List[Dict[str, float]]:
    flat_data = []

    for key, endpoint in DATA_ENDPOINTS.items():
        try:
            response = requests.get(f"{BASE_URL}{endpoint}")
            data = response.json()

            for elt in data:
                try:
                    if key == "csnj":
                        coord_gps = elt["coordonnees_gps"].replace("N", "").replace("E", "").replace("S", "").replace("W", "").replace("/", "").replace(",", ".")
                        latitude, longitude = map(float, coord_gps.split())
                    elif key == "enseignement_superieur":
                        geo = elt.get("Géolocalisation", "").strip()
                        if geo:
                            latitude, longitude = map(float, geo.replace(" ", "").replace(",", " ").split())
                        else:
                            continue
                    else:
                        latitude = float(
                            elt.get("Latitude")
                            or elt.get("Ylat")
                            or elt.get("Y_WGS84")
                            or elt.get("latitude")
                        )
                        longitude = float(
                            elt.get("Longitude")
                            or elt.get("Xlong")
                            or elt.get("X_WGS84")
                            or elt.get("longitude")
                        )
                    flat_data.append({
                        "type": key,
                        "latitude": latitude,
                        "longitude": longitude
                    })
                except Exception as e:
                    print(f"Error processing element {elt}: {e}")

        except requests.RequestException as e:
            print(f"Error fetching data from endpoint {endpoint}: {e}")

    return flat_data
data = get_flat_data()
with open("data.json", "w") as json_file:
    json.dump(data, json_file, indent=4)

