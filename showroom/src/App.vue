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
      gamepad: null,
      btnCount: 8,
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
      clearInterval(this.pollInterval)
      console.log("Gamepad disconnected, poll ended")
    },
    logGamepadStatus() {
      console.log(this.gamepad)
      console.log(this.gamepad.buttons)
      console.log(this.gamepad.axes)
    },
    pollGamepad() {
      this.pollInterval = setInterval(() => {
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
    clearInterval(this.pollInterval)
  }
}
</script>


<template class="container">
  <GlobalEvents target="window" @gamepadconnected="connectGamepad" @gamepaddisconnected="disconnectGamepad" />
  <div v-if="gamepad" class="row">
    <div class="col-sm">
      <div v-for="id in btnCount" class="col-sm">
        <PressButtonIndicator :buttonPressed="gamepad.buttons[id - 1].pressed" :id="id" />
      </div>
    </div>
    <div class="col-sm-2">{{ gamepad.axes }}</div>
    <button type="button" class="col-sm-2 btn btn-primary" @click="logGamepadStatus">Log gamepad</button>
  </div>
  <div v-else>Please connect a gamepad or press a button</div>
</template>

<style scoped></style>
