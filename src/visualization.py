import glob
import json

import folium
import pandas as pd
from shapely.geometry import Point, shape

file_list = glob.glob("../output/state*.csv")
file_list.sort()


def get_color(state):
    if state == 0:
        return 'white'  # No data
    elif state == 1:
        return 'white'  # Normal
    elif state == 2:
        return 'green'  # Slightly worse
    elif state == 3:
        return 'yellow'
    elif state == 4:
        return 'magenta'
    else:
        return 'red'  # Worst condition

def load_data(file_name):
    df = pd.read_csv(file_name, header=None, names=["id", "name", "state", "density"])
    df["state"] = pd.to_numeric(df["state"])
    df["density"] = pd.to_numeric(df["density"])
    return df


for file in file_list:
    data = load_data(file)
    m = folium.Map(location=[10.0452, 105.7469], zoom_start=12)
    geojson = json.load(open("../data/game-map.geojson"))

    def style_function(feature):
        # Retrieve the id from the feature properties
        feature_id = feature['properties'].get('osm_id')  # Use 'ID_3' instead of 'id'
        # Get the corresponding state value from the data
        state = data.loc[data['id'] == feature_id, 'state'].values
        # Handle case where state data might be missing
        color = get_color(state[0]) if len(state) > 0 else 'white'
        return {
            'fillColor': color,
            'color': 'black',
            'weight': 1,
            'fillOpacity': 0.7
        }

    folium.GeoJson(
        geojson,
        style_function=style_function
    ).add_to(m)

    for _, row in data.iterrows():
        feature = next((item for item in geojson['features'] if item['properties']['osm_id'] == row['id']), None)
        if feature:
            # Calculate the centroid of the polygon
            polygon = shape(feature['geometry'])
            point = polygon.centroid
            # Create text with the density information
            folium.Marker(
                [point.y, point.x],
                icon=folium.DivIcon(
                    icon_size=(150,36),
                    icon_anchor=(0,0),
                    html=f'<div style="font-size: 12pt">{row["density"]}</div>',
                )
            ).add_to(m)
    m.save(f'../output/can_tho_map_{file[-5]}.html')
