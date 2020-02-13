import * as React from 'react';
import { View, Text, Button, StyleSheet, TouchableOpacity, AppRegistry } from 'react-native';
import { NavigationContainer } from '@react-navigation/native';
import { createStackNavigator } from '@react-navigation/stack';
import Communications from 'react-native-communications';



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
  <View style={{ flex:1, alignItems: 'center',  backgroundColor: 'white' }}>
  <TouchableOpacity style={styles.customBtnBG3} onPress={() => Communications.phonecall('0695505137', true)}>
  <Text style={styles.customBtnText3}>S.O.S</Text>
  </TouchableOpacity>
  <View style={{ flex:1, alignItems: 'center', justifyContent:'center',  backgroundColor: '#a9a9a9', marginTop:190}}>
  <Text style={styles.customBtnText5}>À titre informatif:</Text>
  <Text style={styles.customBtnText6, {alignItems:'center', fontSize: 20,
  marginTop:0,
  color:'white',
  backgroundColor: "#a9a9a9",
  paddingHorizontal: 20,
  paddingVertical: 0,
  borderRadius: 0,
textAlign:'center',}}>Une utilisation excessive peut entrainer des poursuites.</Text>
  <TouchableOpacity style={styles.customBtnBG5}>
  </TouchableOpacity>
  </View>
  </View>
)
}
function ConfirmationScreen({navigation}) {
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

customBtnText: {
fontSize: 80,
fontWeight: "bold",
color: "orange",
},


customBtnBG: {
backgroundColor: "black",
paddingHorizontal: 40,
paddingVertical: 5,
borderRadius: 35
},


customBtnText2: {
fontSize: 69,
fontWeight: "bold",
color: "black",
},

customBtnBG2: {
backgroundColor: "red",
paddingHorizontal: 30,
paddingVertical: 5,
borderRadius: 35
},
customBtnText3: {

fontSize: 69,
fontWeight: "bold",
color: "red",
},

customBtnBG3: {
  marginTop: 225,
backgroundColor: "black",
paddingHorizontal: 70,
paddingVertical: 100,
borderRadius: 100
},

customBtnBG4: {
marginTop:100,
alignItems:'center',
backgroundColor: "#a9a9a9",
paddingHorizontal: 500,
paddingVertical: 80,
borderRadius: 100


},

customBtnText5: {
fontSize: 18,
marginTop:0,
fontWeight: "bold",
color: "red",
backgroundColor: "#a9a9a9",
paddingHorizontal: 132,
paddingVertical: 0,
borderRadius: 500

},
customBtnText6: {},

});


export default App;
