import React, { Component } from 'react'
import MapView  from 'react-native-maps';
import {StyleSheet, View, TextInput,} from 'react-native';

class Map extends Component {
render(){
  return (
    <View style={styles.container}>,
    <MapView
    style={styles.map}
    initialRegion={{
      latitude: 39.749632,
      longitude: -105.000363,
      latitudeDelta:0.222,
      longitudeDelta:0.0201,}}/>
      <TextInput/>
      </View>
  );
}
}
const styles = StyleSheet.create({
  container: {
    flex:1,
    justifyContent: 'center',
    alignItems: 'center',
    backgroundColor: '#F5FCFF',
  },
  map: {
    ...StyleSheet.absoluteFillObject,
  },
});
export default Map;
