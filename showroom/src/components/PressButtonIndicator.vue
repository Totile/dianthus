<script>
export default {
    props: {
        buttonPressed: Boolean,
        id: Number,
    }
}
</script>

<template>
    <div>
        <div class="alert alert-primary" v-if="buttonPressed">Button {{ id }}</div>
        <div class="alert alert-danger" v-else>Button {{ id }}</div>
    </div>
</template>
