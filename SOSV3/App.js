import * as React from 'react';
import { View, Text, Button, StyleSheet, TouchableOpacity } from 'react-native';
import { NavigationContainer } from '@react-navigation/native';
import { createStackNavigator } from '@react-navigation/stack';

function HomeScreen({navigation}) {
  return (
    <View style={{ flex:1, backgroundColor: 'yellow' }}>
    <View style={{ flex:1, alignItems: 'center', justifyContent: 'center',  height: 335, backgroundColor: 'white' }}>
    <TouchableOpacity style={styles.customBtnBG} onPress={() => navigation.navigate('Validation')}>
  <Text style={styles.customBtnText}>Pour moi</Text>
  </TouchableOpacity>
  </View>
    <View style={{ flex:1, alignItems: 'center', justifyContent: 'center',  height: 335, backgroundColor: 'black' }}>
    <TouchableOpacity style={styles.customBtnBG2} onPress={() => navigation.navigate('Validation')}>
  <Text style={styles.customBtnText2}>Pour autrui</Text>
  </TouchableOpacity>
  </View>
    </View>
  );
}
function ValidateScreen({navigation}) {
  return(
  <View style={{ flex:1, backgroundColor: 'yellow' }}>
  <TouchableOpacity style={styles.customBtnBG3} onPress={() => navigation.navigate('Validation')}>
<Text style={styles.customBtnText2}>S.O.S</Text>
</TouchableOpacity>
  </View>
)
}
function ConfirmationScreen({navigation}) {
  return(
  <View style={{ flex:1, backgroundColor: 'yellow' }}>

  </View>
)
}
const Stack = createStackNavigator();

function App() {
  return (
    <NavigationContainer>
      <Stack.Navigator>
        <Stack.Screen name="Home" component={HomeScreen} />
        <Stack.Screen name="Validation" component={ValidateScreen} />
        <Stack.Screen name="Confirmation" component={ConfirmationScreen} />

      </Stack.Navigator>
    </NavigationContainer>
  );
}
const styles = StyleSheet.create({
/* Here style the text of your button */
customBtnText: {
fontSize: 80,
fontWeight: "bold",
color: "orange",
},

/* Here style the background of your button */
customBtnBG: {
backgroundColor: "black",
paddingHorizontal: 40,
paddingVertical: 5,
borderRadius: 35
},
/* Here style the text of your button */
customBtnText2: {
fontSize: 69,
fontWeight: "bold",
color: "black",
},

/* Here style the background of your button */
customBtnBG2: {
backgroundColor: "orange",
paddingHorizontal: 30,
paddingVertical: 5,
borderRadius: 35
},
customBtnText3: {
fontSize: 69,
fontWeight: "bold",
color: "black",
},
/* Here style the background of your button */
customBtnBG3: {
backgroundColor: "orange",
paddingHorizontal: 30,
paddingVertical: 5,
borderRadius: 35
}
});


export default App;
