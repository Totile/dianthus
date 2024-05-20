<script>
import HelloWorld from './components/HelloWorld.vue'
import TheWelcome from './components/TheWelcome.vue'
import PressButtonIndicator from './components/PressButtonIndicator.vue';
import { GlobalEvents } from 'vue-global-events';

export default {
  components: {
    PressButtonIndicator,
    GlobalEvents,
  },
  data() {
    return {
      gamepad: null
    }
  },
  mounted() {
    /* window.addEventListener("gamepadconnected", (e) => {
      console.log(
        "Gamepad connected at index %d: %s. %d buttons, %d axes.",
        e.gamepad.index,
        e.gamepad.id,
        e.gamepad.buttons.length,
        e.gamepad.axes.length,
      );
      this.gamepad = e.gamepad
    }); */
  },
  methods: {
    connectGamepad(event) {
      console.log(
        "Gamepad connected at index %d: %s. %d buttons, %d axes.",
        event.gamepad.index,
        event.gamepad.id,
        event.gamepad.buttons.length,
        event.gamepad.axes.length,
      );
      this.gamepad = navigator.getGamepads()[event.gamepad.index];
      this.pollGamepad();
      console.log("poll started")
    },
    disconnectGamepad(event) {
      this.gamepad = null
      clearInterval(this.pollGamepad)
      console.log("Gamepad disconnected, poll ended")
    },
    showGamepadStatus() {
      console.log(this.gamepad.buttons)
      console.log(this.gamepad.buttons[2])
      console.log(this.gamepad.buttons[0].pressed)
    },
    pollGamepad() {
      this.pollGamepad = setInterval(() => {
        this.gamepad = navigator.getGamepads()[0];
        // console.log(this.gamepad)
      }, 25)
    },
  },
  computed: {
    buttons() {
      return this.gamepad.buttons
    }
  },
  beforeDestroy() {
    clearInterval(this.pollGamepad)
  }
}
</script>


<template class="container">
  <GlobalEvents target="window" @gamepadconnected="connectGamepad" @gamepaddisconnected="disconnectGamepad" />
  <div class="row">
    <div class="col">
      <img alt="Vue logo" src="./assets/logo.svg" width="125" height="125" />

    </div>
    <div class="col">
      <button class="btn btn-danger alert alert-danger" :disabled="!gamepad || !gamepad.connected"
        @click="showGamepadStatus">
        btn1</button>
    </div>

    <div class="col">
      <PressButtonIndicator />
    </div>
  </div>
</template>

<style scoped></style>
