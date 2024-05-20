<script>
export default {
    data() {
        return {
            count: 0
        }
    },
    methods: {
        increment() {
            this.count++
        }
    },
    mounted() {
        this.increment()
    }
}
</script>

<template>
    test press
</template>
